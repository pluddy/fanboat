#include <ros/ros.h>
#include <math.h>

class visualArbitrator
{
public:
	visualArbitrator();

	//Private functions/variables
private:

	void ball_callback(const ball_detector::ballLocation::ConstPtr& msg);
	void land_callback(const landmark_self_sim::landmarkLocation::ConstPtr& msg);
	void has_ball_callback(const lab3::hasBall::ConstPtr& msg);


	ros::NodeHandle nh_;

	ros::Publisher ball_land_pub_;
  ros::Publisher land_pub_;
	ros::Subscriber ball_sub_;
  ros::Subscriber has_ball_sub_;
	ros::Subscriber land_sub_;
};

//Set values to read from xbox controller
visualArbitrator::visualArbitrator():
	{
		//Subscribe to joy_constant for button controls to arbitrate
		ball_sub_ =  nh_.subscribe<ball_detector::ballLocation>("ballLocation", 1, &visualArbitrator::ball_callback, this);
		land_sub_ =  nh_.subscribe<landmark_self_sim::landmarkLocation>("landmarkLocation", 1, &visualArbitrator::land_callback, this);
		has_ball_sub_ = nh_.subscribe<lab3::hasBall>("hasBall",1, &visualArbitrator::has_ball_callback, this);
		//Subscribe to topics to arbitrate between
		//Publish arbitrated values to angle_joy
		ball_land_pub_ = nh_.advertise<lab3::ballLandInfo>("ballLandInfo", 1);
	}

	bool lookForBall = true;
	void visualArbitrator::ball_callback(const ball_detector::ballLocation::ConstPtr& msg){
		if(lookForBall == true){
			lab3::ballLandInfo info;
			info.x = msg->x;
			info.y = msg->y;
			info.distance = msg->distance;
			info.type = 1;
			ball_land_pub_.publish(info);
		}
	}
	void visualArbitrator::land_callback(const landmark_self_sim::landmarkLocation::ConstPtr& msg){
		if(lookForBall != true){
			lab3::ballLandInfo info;
			info.x = (msg->xtop + msg->xbottom) /2;
			info.y = (msg->ytop + msg->ybottom) /2;
			info.distance = msg->distance;
			info.type = 0;
			ball_land_pub_.publish(info);
		}
	}
	void visualArbitrator::has_ball_callback(const lab3::hasBall::ConstPtr& msg){
		if(msg->hasBall == 1){
			lookForBall = false;
		}
		else{
			lookForBall = true;
		}
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