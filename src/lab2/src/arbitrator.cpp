#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <lab2/angle_msg.h>
#include <fanboat_ll/fanboatMotors.h>
#include <fanboat_ll/fanboatLL.h>
#include <math.h>

class arbitrator
{
public:
	arbitrator();

	//Private functions/variables
private:
	void joy_callback(const sensor_msgs::Joy::ConstPtr& joy);
	void angle_joy_callback(const lab2::angle_msg::ConstPtr& ang);
	void angle_tri_callback(const lab2::angle_msg::ConstPtr& ang);
	void angle_rc_callback(const lab2::angle_msg::ConstPtr& ang);

	ros::NodeHandle nh_;
	int lb_, a_button_, b_button_, y_button_;

	ros::Publisher arb_pub;
	ros::Subscriber angle_joy_sub_;
	ros::Subscriber angle_tri_sub_;
	ros::Subscriber angle_rc_sub_;
	ros::Subscriber joy_sub_;
};

//Set values to read from xbox controller
arbitrator::arbitrator():
	a_button_(0), //joystick
	b_button_(1), //rc
	y_button_(3), //triangle
	lb_(4)      //on
{
	//Subscribe to joy_constant for button controls to arbitrate
	joy_sub_ =  nh_.subscribe<sensor_msgs::Joy>("joy_constant", 1, &arbitrator::joy_callback, this);
	
	//Subscribe to topics to arbitrate between
	angle_joy_sub_ = nh_.subscribe<lab2::angle_msg>("angle_joy", 1, &arbitrator::angle_joy_callback, this);
	angle_tri_sub_ = nh_.subscribe<lab2::angle_msg>("angle_tri", 1, &arbitrator::angle_tri_callback, this);
	angle_rc_sub_ = nh_.subscribe<lab2::angle_msg>("angle_rc", 1, &arbitrator::angle_rc_callback, this);

	//Publish arbitrated values to angle_joy
	arb_pub = nh_.advertise<lab2::angle_msg>("angle_arb", 1);

}

//Variables to communicate left/right motor power and current/final yaw values
bool on = true;
int arb_value = 0; //0 = joy, 1 = tri, 2 = rc, else publish 0's

//If this topic should be forwarded, forward it
//If off or 
void arbitrator::angle_joy_callback(const lab2::angle_msg::ConstPtr& ang)
{ 
	lab2::angle_msg msg;
	msg.angle = ang->angle;
	msg.thrust = ang->thrust;
	
	if(on && arb_value == 0) {
		arb_pub.publish(msg);
	} else if(!on || arb_value < 0 || arb_value > 0) {
		msg.angle = 0;
		msg.thrust = 0;
		arb_pub.publish(msg);
	}
}

//If this topic should be forwarded, forward it
void arbitrator::angle_tri_callback(const lab2::angle_msg::ConstPtr& ang)
{ 
	lab2::angle_msg msg;
	msg.angle = ang->angle;
	msg.thrust = ang->thrust;
	if(on && arb_value == 1) {
		arb_pub.publish(msg);
	}
}

//If this topic should be forwarded, forward it
void arbitrator::angle_rc_callback(const lab2::angle_msg::ConstPtr& ang)
{ 
	lab2::angle_msg msg;
	msg.angle = ang->angle;
	msg.thrust = ang->thrust;
	if(on && arb_value == 2) {
		arb_pub.publish(msg);
	}
}

//Read input from the joystick
void arbitrator::joy_callback(const sensor_msgs::Joy::ConstPtr& joy)
{
	if(joy->buttons[lb_]) on = !on;
	if(joy->buttons[a_button_]) { //A is joystick
		arb_value = 0;
	} else if(joy->buttons[b_button_]) { //B is rc
		arb_value = 2;
	} else if(joy->buttons[y_button_]) { //Y is triangle
		arb_value = 1;
	}
}

int main(int argc, char** argv)
{

	ros::init(argc, argv, "arbitrator");
	arbitrator arbitrator;

	ros::spin();
}
