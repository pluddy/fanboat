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
	int lb_, a_button_, b_button_, y_button_, up_d_pad_, down_d_pad_, left_d_pad_, right_d_pad_, left_joy_button_;

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
	lb_(4),    //on
	up_d_pad_(13), //set angle to 0deg
	down_d_pad_(14), //set angle to -180/180deg
	left_d_pad_(11), //set angle to -90deg
	right_d_pad_(12), //set angle to 90deg
	left_joy_button_(9) //reset the dpad

	{
	//Subscribe to joy_constant for button controls to arbitrate
		joy_sub_ =  nh_.subscribe<sensor_msgs::Joy>("joy", 1, &arbitrator::joy_callback, this);

	//Subscribe to topics to arbitrate between
		angle_joy_sub_ = nh_.subscribe<lab2::angle_msg>("angle_joy", 1, &arbitrator::angle_joy_callback, this);
		angle_tri_sub_ = nh_.subscribe<lab2::angle_msg>("angle_tri", 1, &arbitrator::angle_tri_callback, this);
		angle_rc_sub_ = nh_.subscribe<lab2::angle_msg>("angle_rc", 1, &arbitrator::angle_rc_callback, this);

	//Publish arbitrated values to angle_joy
		arb_pub = nh_.advertise<lab2::angle_msg>("angle_arb", 1);

	}

//Variables to communicate left/right motor power and current/final yaw values
bool on = false;
int arb_value = 0; //0 = joy, 1 = tri, 2 = rc, else publish 0's
bool up = false, down = false, left = false, right = false;
//If this topic should be forwarded, forward it
//If off or 
void arbitrator::angle_joy_callback(const lab2::angle_msg::ConstPtr& ang)
{ 
	lab2::angle_msg msg;
	msg.angle = ang->angle;
	msg.thrust = ang->thrust;
	
	if(on && arb_value == 0) {
		if(up == true){
			msg.angle = 0.0;
			msg.thrust = .3;
			//ROS_INFO("UP");
		}
		else if(down == true){
			msg.angle = 180.0;
			msg.thrust = .3;
			//ROS_INFO("DOWN");

		}
		else if(left == true){
			msg.angle = -90.0;
			msg.thrust = .3;
			//ROS_INFO("LEFT");

		}
		else if(right == true){
			msg.angle = 90.0;
			msg.thrust = .3;
			//ROS_INFO("RIGHT");

		}
		arb_pub.publish(msg);
	} else if(!on || arb_value < 0 || arb_value > 2) {
		msg.angle = 0;
		msg.thrust = 0;
		//arb_pub.publish(msg);
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
	//if(joy->buttons[lb_]) on = !on;
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
		
		//ROS_INFO("abutton? up: %d, down: %d, left: %d, right: %d", up, down, left, right);

	} else if(joy->buttons[b_button_]) { //B is rc
		arb_value = 2;
	} else if(joy->buttons[y_button_]) { //Y is triangle
		arb_value = 1;
	}

	if(arb_value == 0){
		if(joy->buttons[up_d_pad_]){
			up = true;
			down = false;
			left = false;
			right = false;
		}
		else if(joy->buttons[down_d_pad_]){
			up = false;
			down = true;
			left = false;
			right = false;
		}
		else if(joy->buttons[left_d_pad_]){
			up = false;
			down = false;
			left = true;
			right = false;
		}
		else if(joy->buttons[right_d_pad_]){
			up = false;
			down = false;
			left = false;
			right = true;
		}
		else if(joy->buttons[left_joy_button_]){
			up = false;
			down = false;
			left = false;
			right = false;
		}

	}

}

int main(int argc, char** argv)
{

	ros::init(argc, argv, "arbitrator");
	arbitrator arbitrator;

	ros::spin();
}
