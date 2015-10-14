#include <ros/ros.h>
#include <lab2/angle_msg.h>
#include <fanboat_ll/fanboatMotors.h>
#include <fanboat_ll/fanboatLL.h>
#include <math.h>

class angularPositionPID
{
public:
	angularPositionPID();
	


	//Private functions/variables
private:
	void angle_callback(const lab2::angle_msg::ConstPtr& ang);
	void fanboatLL_callback(const fanboat_ll::fanboatLL::ConstPtr& ang);

	ros::NodeHandle nh_;

	ros::Publisher motors_pub_;

	ros::Subscriber angle_sub_;
	ros::Subscriber fanboatLL_sub_;
	
};

double pValue;
double dValue;
double rightScale;
double leftScale;
angularPositionPID::angularPositionPID()
{
	//Subscribe to arbitated angle messages
	fanboatLL_sub_ =  nh_.subscribe<fanboat_ll::fanboatLL>("sensors", 1, &angularPositionPID::fanboatLL_callback, this);

	//Subscribe to topics to arbitrate between
	angle_sub_ = nh_.subscribe<lab2::angle_msg>("angle_arb", 1, &angularPositionPID::angle_callback, this);

	//Publish to motors topic
	motors_pub_ = nh_.advertise<fanboat_ll::fanboatMotors>("motors", 1);


	nh_.getParam("pValue", pValue);
	nh_.getParam("dValue", dValue);
	nh_.getParam("rightScale", rightScale);
	nh_.getParam("leftScale", leftScale);
	

}

//Variables

lab2::angle_msg ang;
fanboat_ll::fanboatLL fll;
double left,right;
double previousDiff = 0;
int state = 0;

//pulled from the arduino library.
double map(double x, double in_min, double in_max, double out_min, double out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void anglepid(double target)
{
	double diff = target - fll.yaw;
	diff = (diff > 180) ? diff-360 : (diff < -180)? diff + 360 : diff;
	ROS_INFO("diff = %f ",diff);
	double P = 1/pValue;
	double D = dValue;
	double error = diff - previousDiff;
	previousDiff = diff;
	double dFactor = D*error;
	ROS_INFO("pFactor = %f dFactor = %f", P*diff, dFactor);
	if(diff > 0) {
		left = P*diff + dFactor;
		if(left > 1) left=1;
		left = map(left, 0.0,1.0,.45,.7);
		left = left * leftScale;
		
	} else {
		right = P*(-1*diff) - dFactor;
		if(right > 1) right=1;
		right = map(right, 0.0,1.0,.3,.5);
		right = right * rightScale;
	}

	ROS_INFO("left = %f right = %f", left, right);
}

int count;
double straight = 0.35;
double turn = 0.2;
double publishes = 27;
//Get driving info and publish to fanboatLL
void angularPositionPID::angle_callback(const lab2::angle_msg::ConstPtr& am)
{
	fanboat_ll::fanboatMotors boat;
	left = am->thrust;
	right = am->thrust;

	anglepid(am->angle);

	boat.left = left;
	boat.right = right;

	motors_pub_.publish(boat);
}

//Get feedback from fanboat
void angularPositionPID::fanboatLL_callback(const fanboat_ll::fanboatLL::ConstPtr& f_ll)
{
	fll = *f_ll;
}

int main(int argc, char** argv)
{
	
	ros::init(argc, argv, "angularPositionPID");
	angularPositionPID angularPositionPID;

	ros::spin();
}
