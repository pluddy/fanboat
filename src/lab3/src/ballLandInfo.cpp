#include <ros/ros.h>
#include <lab3/ballLandInfo.h>
#include <landmark_self_sim/landmarkLocation.h>
#include <ball_detector/ballLocation.h>
#include <lab3/hasBall.h>
#include <math.h>

class ballLandInfo
{
public:
	ballLandInfo();

	//Private functions/variables
private:

	void ball_callback(const ball_detector::ballLocation::ConstPtr& msg);
	void land_callback(const landmark_self_sim::landmarkLocation::ConstPtr& msg);
	void has_ball_callback(const lab3::hasBall::ConstPtr& msg);


	ros::NodeHandle nh_;

	ros::Publisher ball_land_pub_;

	ros::Subscriber ball_sub_;
  ros::Subscriber has_ball_sub_;
	ros::Subscriber land_sub_;
};

//Set values to read from xbox controller
ballLandInfo::ballLandInfo()
{
	//Subscribe to joy_constant for button controls to arbitrate
	ball_sub_ =  nh_.subscribe<ball_detector::ballLocation>("ballLocation", 1, &ballLandInfo::ball_callback, this);
	land_sub_ =  nh_.subscribe<landmark_self_sim::landmarkLocation>("landmarkLocation", 1, &ballLandInfo::land_callback, this);
	has_ball_sub_ = nh_.subscribe<lab3::hasBall>("hasBall",1, &ballLandInfo::has_ball_callback, this);
	//Subscribe to topics to arbitrate between
	//Publish arbitrated values to angle_joy
	ball_land_pub_ = nh_.advertise<lab3::ballLandInfo>("ballLandInfo", 1);
}

bool lookForBall = true;
void ballLandInfo::ball_callback(const ball_detector::ballLocation::ConstPtr& msg){
	if(lookForBall == true){
		lab3::ballLandInfo info;
		info.x = msg->x;
		info.y = msg->y;
		info.distance = msg->distance;
		info.type = 1;
		ball_land_pub_.publish(info);
	}
}
void ballLandInfo::land_callback(const landmark_self_sim::landmarkLocation::ConstPtr& msg){
	if(lookForBall != true){
		lab3::ballLandInfo info;
		int xtop = msg->xtop;
		int ytop = msg->ytop;
		int xbottom = msg->xbottom;
		int ybottom = msg->ybottom;
		int height = msg->height;

		int width = (11/8.5)*height;

		int x = ((xtop + xbottom)/2) - width/2;

		info.x = x;
		info.y = (ytop + ybottom) /2;
		info.distance = msg->distance;
		info.type = 0;
		ball_land_pub_.publish(info);
	}
}
void ballLandInfo::has_ball_callback(const lab3::hasBall::ConstPtr& msg){
	if(msg->hasBall == 1){
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
