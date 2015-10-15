#include <ros/ros.h>
#include <lab2/angle_msg.h>
#include <sensor_msgs/Joy.h>
#include <fanboat_ll/fanboatMotors.h>
#include <fanboat_ll/fanboatLL.h>
#include <math.h>

class reactiveControl
{
public:
	reactiveControl();
	ros::Publisher angles_pub_;
	
	//Private functions/variables
private:
	//void angle_callback(const lab2::angle_msg::ConstPtr& ang);
	void joy_callback(const sensor_msgs::Joy::ConstPtr& joy);

	void sensorFilter_callback(const fanboat_ll::fanboatLL::ConstPtr& ang);
	ros::NodeHandle nh_;
	int right_joy_button_;
	ros::Subscriber joy_sub_;

	ros::Subscriber sensors_sub_;
	
};

double pValue;
double dValue;
double rightScale;
double leftScale;
reactiveControl::reactiveControl():
right_joy_button_(10) //reset the diff
{
//Subscribe to arbitated angle messages
	sensors_sub_ = nh_.subscribe<fanboat_ll::fanboatLL>("sensors", 1, &reactiveControl::sensorFilter_callback, this);

	joy_sub_ =  nh_.subscribe<sensor_msgs::Joy>("joy", 1, &reactiveControl::joy_callback, this);

//Publish to angles topic
	angles_pub_ = nh_.advertise<lab2::angle_msg>("angle_rc", 1);

}

//Variables
double rangeAllowance = 30;
fanboat_ll::fanboatLL fll;
double initLeftS = -100;
double initRightS = -100;
double init = -1000;
double leftS, rightS, rightMotor, leftMotor, angle, thrust, diffL, diffR;
bool isMapping = false;
bool isForward = true;

//pulled from the arduino library.
double map(double x, double in_min, double in_max, double out_min, double out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

bool rightInRange(){
	if(diffR > -rangeAllowance && diffR < rangeAllowance){
		return true;
	}
	return false;
}

bool leftInRange(){
	if(diffL > -rangeAllowance && diffL < rangeAllowance){
		return true;
	}
	return false;
}

void reactive()
{
	diffL = initLeftS - leftS;
	diffR = initRightS - rightS;
	double currentA = fll.yaw;
	double thrustDiff = .02;
	thrust = 0.2;
	if(leftS < 200 && rightS < 200) {
		thrust = 0.2;
		angle = currentA;
	}
	//both in range go straight
	else if(rightInRange() && leftInRange()){
		thrust = .2;
		angle = currentA;
	}
	//when both below -50 slow down
	else if(diffR <= 0 && diffL <= 0){
		thrust = 0.2;
		angle = currentA;
	}
	//when dif r > 50 and l is in range l slow down 
	else if(leftInRange() && diffR >= rangeAllowance){
		angle = currentA - 20;
	}
	//when dif l > 50 and r is in range r slow down
	else if(rightInRange() && diffL >= rangeAllowance){
		angle = currentA + 20;
	}
	//when diff l < -50 and r is in range l slow down
	else if(rightInRange() && diffL <= -rangeAllowance){
		angle = currentA - 20;
	}
	//when diff r < -50 and l is in range r slow down
	else if(leftInRange() && diffR <= -rangeAllowance){
		angle = currentA + 20;
	}
	else if(diffL <=-rangeAllowance && diffR >= rangeAllowance){
		angle = currentA - 40;
	}
	else if(diffL >= rangeAllowance && diffR <= -rangeAllowance){
		angle = currentA + 40;
	}
	//when both above 50 speed up
	else if(diffR >= rangeAllowance && diffL >= rangeAllowance){
		angle = currentA;
		thrust = .35;
	}
	else{
		ROS_INFO("NO STATE HIT");
		ROS_INFO("NO STATE HIT");
		ROS_INFO("NO STATE HIT");
		ROS_INFO("NO STATE HIT");
		ROS_INFO("NO STATE HIT");
	}

	if(thrust < .25) thrust = .25;
	if(thrust > .5) thrust = .5;

	ROS_INFO("diffL = %lf diffR = %lf angle = %lf thrust = %lf", diffL, diffR, angle,thrust);
	//ROS_INFO("leftS = %f, rightS = %f", leftS, rightS);
}


void reactiveControl::joy_callback(const sensor_msgs::Joy::ConstPtr& joy){
	if(joy->buttons[right_joy_button_]) { 
		initLeftS = leftS;
		initRightS = rightS;		
	}
}



//we want the boat to stay within 350-425 range finders for sensors
//Get feedback from fanboat
void reactiveControl::sensorFilter_callback(const fanboat_ll::fanboatLL::ConstPtr& f_ll)
{
	fll = *f_ll;
	lab2::angle_msg boat;

//ROS_INFO("reactiveControl");
	leftS = fll.a0;
	rightS = fll.a1;
	if (initLeftS == -100){
		initLeftS = leftS;
	}
	if (initRightS == -100){
		initRightS = rightS;
	}
	reactive();

	boat.angle = angle;
	boat.thrust = thrust;
	angles_pub_.publish(boat);
}




int main(int argc, char** argv)
{

	ros::init(argc, argv, "reactiveControl");
	reactiveControl reactiveControl;


	ros::spin();
}
