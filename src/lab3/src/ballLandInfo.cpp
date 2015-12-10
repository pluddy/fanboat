#include <ros/ros.h>
#include <lab3/ballLandInfo.h>
#include <landmark_self_sim/landmarkLocation.h>
#include <ball_detector/ballLocation.h>
#include <lab3/hasBall.h>
#include <project/rocket_msg.h>
#include <math.h>

class ballLandInfo
{
public:
	ballLandInfo();

	//Private functions/variables
private:

	void ball_callback(const ball_detector::ballLocation::ConstPtr& msg);
	void land_callback(const landmark_self_sim::landmarkLocation::ConstPtr& msg);
	void rocket_fire_callback(const project::rocket_msg::ConstPtr& msg);


	ros::NodeHandle nh_;

	ros::Publisher ball_land_pub_;

	ros::Subscriber ball_sub_;
  ros::Subscriber rocket_fire_sub_;
	ros::Subscriber land_sub_;
};

//Set values to read from xbox controller
ballLandInfo::ballLandInfo()
{
	//Subscribe to joy_constant for button controls to arbitrate
	ball_sub_ =  nh_.subscribe<ball_detector::ballLocation>("ballConstant", 1, &ballLandInfo::ball_callback, this);
	land_sub_ =  nh_.subscribe<landmark_self_sim::landmarkLocation>("landConstant", 1, &ballLandInfo::land_callback, this);
	rocket_fire_sub_ = nh_.subscribe<project::rocket_msg>("launcher_topic",1, &ballLandInfo::rocket_fire_callback, this);
	//Subscribe to topics to arbitrate between
	//Publish arbitrated values to angle_joy
	ball_land_pub_ = nh_.advertise<lab3::ballLandInfo>("ballLandInfo", 1);
}

bool lookForBall = true;
void ballLandInfo::ball_callback(const ball_detector::ballLocation::ConstPtr& msg){
	if(lookForBall){
		lab3::ballLandInfo info;
		info.x = msg->x;
		info.y = msg->y;
		info.distance = msg->distance;
		info.type = 1;
		info.id = -5;
		ball_land_pub_.publish(info);
	}
}
void ballLandInfo::land_callback(const landmark_self_sim::landmarkLocation::ConstPtr& msg){
	if(!lookForBall){
		lab3::ballLandInfo info;
		int xtop = msg->xtop+320;
		int ytop = msg->ytop;
		int xbottom = msg->xbottom+320;
		int ybottom = msg->ybottom;
		int height = msg->height;
		int id = msg->code;
		int width = (11/8.5)*height;

		int x = ((xtop + xbottom)/2) - width/2;
		x -= 320;
		info.x = x;
		info.y = (ytop + ybottom) /2;
		info.distance = msg->distance;
		info.type = 0;
		info.id = id;
		info.header.stamp = ros::Time::now();
//		ROS_INFO("hurdurhur");
		ball_land_pub_.publish(info);
	}
}

void ballLandInfo::rocket_fire_callback(const project::rocket_msg::ConstPtr& msg){
	if(msg->state >= 1){
		lookForBall = false;
	}
	else{
		lookForBall = true;
	}
}

int main(int argc, char** argv)
{

	ros::init(argc, argv, "ballLandInfo");
	ballLandInfo ballLandInfo;

	ros::spin();
}
