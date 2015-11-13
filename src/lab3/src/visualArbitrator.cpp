#include <ros/ros.h>
#include <math.h>

class visualArbitrator
{
public:
	visualArbitrator();

	//Private functions/variables
private:

	void image_callback(const lab3::image_msg::ConstPtr& image);


	ros::NodeHandle nh_;

	ros::Publisher ball_pub_;
  ros::Publisher land_pub_;
	ros::Subscriber image_sub_;
  ros::Subscriber has_ball_sub_;
};

//Set values to read from xbox controller
visualArbitrator::visualArbitrator():
	{
	//Subscribe to joy_constant for button controls to arbitrate
		image_sub_ =  nh_.subscribe<sensor_msgs::Joy>("joy", 1, &visualArbitrator::image_callback, this);

	//Subscribe to topics to arbitrate between
		//Publish arbitrated values to angle_joy
		ball_pub_ = nh_.advertise<lab2::angle_msg>("angle_arb", 1);

	}


void image_callback(const lab3::image_msg::ConstPtr& image){
  
}

//Variables to communicate left/right motor power and current/final yaw values
//If this topic should be forwarded, forward it
//If off or
// void visualArbitrator::angle_joy_callback(const lab2::angle_msg::ConstPtr& ang)
// {
// 	lab2::angle_msg msg;
// 	msg.angle = ang->angle;
// 	msg.thrust = ang->thrust;
//
//
// 	if(on && arb_value == 0) {
// 		if(up == true){
// 			msg.angle = 0.0;
// 			msg.thrust = .2;
// 			//ROS_INFO("UP");
// 		}
// 		else if(down == true){
// 			msg.angle = 180.0;
// 			msg.thrust = .2;
// 			//ROS_INFO("DOWN");
//
// 		}
// 		else if(left == true){
// 			msg.angle = -90.0;
// 			msg.thrust = .2;
// 			//ROS_INFO("LEFT");
//
// 		}
// 		else if(right == true){
// 			msg.angle = 90.0;
// 			msg.thrust = .2;
// 			//ROS_INFO("RIGHT");
//
// 		}
// 		arb_pub.publish(msg);
// 	} else if(!on || arb_value < 0 || arb_value > 2) {
// 		msg.angle = 0;
// 		msg.thrust = 0;
// 		//arb_pub.publish(msg);
// 	}
// }





int main(int argc, char** argv)
{

	ros::init(argc, argv, "visualArbitrator");
	visualArbitrator visualArbitrator;

	ros::spin();
}
