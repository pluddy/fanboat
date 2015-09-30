#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <math.h>
class joy_constant
{
public:
	joy_constant();

	//private variables that can be used in joy callback
private:
	void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);

	ros::NodeHandle nh_;
	ros::Subscriber joy_sub_;

};

//all the buttons/axis that we used
joy_constant::joy_constant()
{
	joy_sub_ =  nh_.subscribe<sensor_msgs::Joy>("joy", 1, &joy_constant::joyCallback, this);
}

sensor_msgs::Joy joy_values;
//callback/interrupt
void joy_constant::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
	joy_values.axes = joy->axes;
	joy_values.buttons = joy->buttons;
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "joy_constant");
	joy_constant joy_constant;
	ros::Rate loop_rate(13);//set frequency to 13Hz
	ros::NodeHandle nh;
	ros::Publisher pub = nh.advertise<sensor_msgs::Joy>("joy_constant", 1);//publisher

	//Continually publish the latest joy messages to joy_constant
	while(ros::ok()) {
		pub.publish(joy_values);

		ros::spinOnce();//spin
		loop_rate.sleep();
	}
	ros::spin();
}

