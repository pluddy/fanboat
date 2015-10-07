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

angularPositionPID::angularPositionPID()
{
	//Subscribe to arbitated angle messages
	fanboatLL_sub_ =  nh_.subscribe<fanboat_ll::fanboatLL>("fanboatLL", 1, &angularPositionPID::fanboatLL_callback, this);

	//Subscribe to topics to arbitrate between
	angle_sub_ = nh_.subscribe<lab2::angle_msg>("angle_arb", 1, &angularPositionPID::angle_callback, this);

	//Publish to motors topic
	motors_pub_ = nh_.advertise<fanboat_ll::fanboatMotors>("motors", 1);

}

//Variables
lab2::angle_msg ang;
fanboat_ll::fanboatLL fll;
double left,right;
double init = -1000;
double previousDiff = 0;

void anglepid(double target)
{
	
	double diff = target - (fll.yaw-init);
	diff = (diff > 180) ? diff-360 : (diff < -180)? diff + 360 : diff;
	ROS_INFO("diff = %f ",diff);
	double P = 1/250.0;
	double D = .05;
	double error = diff - previousDiff;
	previousDiff = diff;
	double dFactor = D*error;
	if(diff > 0){
		left = P*diff + dFactor;
		left = (left * .7) + 0.3;
		left = left * 1.1;
		left = 1;
	right = .15;
	} else {
		right = P*(180 - diff) - dFactor;
		right = (right * .7) + 0.3;
		right = right * .4;
		left = .15;
	right = 1;
	}

	ROS_INFO("left = %f right = %f", left, right);
}

//Get driving info and publish to fanboatLL
void angularPositionPID::angle_callback(const lab2::angle_msg::ConstPtr& am)
{
	fanboat_ll::fanboatMotors boat;
	left = 0.15;
	right = 0.15;
	ROS_INFO("angle = %f  left = %f  right = %f", am->angle, left,right);
	if(!am->thrust <= .05){
		anglepid(am->angle);
	}

	boat.left = left;
	boat.right = right;

	//TODO: Call a function to do PID stuff here

	motors_pub_.publish(boat);
}

//Get feedback from fanboat
void angularPositionPID::fanboatLL_callback(const fanboat_ll::fanboatLL::ConstPtr& f_ll)
{
	fll = *f_ll;
	fll.yaw = fll.yaw - 360;
	if(init == -1000){
		init = fll.yaw;
	}
}

int main(int argc, char** argv)
{

	ros::init(argc, argv, "angularPositionPID");
	angularPositionPID angularPositionPID;

	ros::spin();
}
