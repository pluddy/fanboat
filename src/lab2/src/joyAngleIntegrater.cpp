#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <lab2/angle_msg.h>
#include <math.h>
class joyAngleIntegrater
{
public:
	joyAngleIntegrater();

	//private variables that can be used in joy callback
private:
	void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);

	ros::NodeHandle nh_;

	double x_, y_;

	ros::Subscriber joy_sub_;
	ros::Publisher ang_pub;
};

//all the buttons/axis that we used
joyAngleIntegrater::joyAngleIntegrater():
	x_(0),
	y_(1)
{
	joy_sub_ =  nh_.subscribe<sensor_msgs::Joy>("joy_constant", 1, &joyAngleIntegrater::joyCallback, this);
	ang_pub = nh_.advertise<lab2::angle_msg>("angle_joy", 1);
}

double angle, thrust;

//callback/interrupt
void joyAngleIntegrater::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
	double x = joy->axes[x_];
	double y = joy->axes[y_];

	//Calculate thrust
	double thrust = sqrt(x * x + y * y);
	if(thrust > 1.0) thrust = 1.0;
	if(thrust < 0.0) thrust = 0.0;

	//Calculate angle
	double angle;
	if(x == 0) {
		angle = (y >= 0) ? 90 : 270; //Avoid dividing by 0 if stick is up or down
	} else {
		angle = atan(y / x) / M_PI * 180; //Get angle in degrees
	}
	angle = (360 - angle) + 90; //Adjust so that 0 is forward and degrees are clockwise (90 is right)
	if(angle >= 360.0) {
		angle -= 360;
	}

	//Publish the angle_msg
	lab2::angle_msg msg;
	msg.thrust = thrust;
	msg.angle = angle;

	ang_pub.publish(msg);
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "joyAngleIntegrater");
	joyAngleIntegrater joyAngleIntegrater;

	ros::spin();
}

