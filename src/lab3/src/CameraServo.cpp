#include <ros/ros.h>
#include <landmark_self_sim/landmarkLocation.h>
#include <lab2/angle_msg.h>
#include <lab3/ballLandInfo.h>
#include <fanboat_ll/fanboatMotors.h>
#include <fanboat_ll/fanboatLL.h>
#include <math.h>
using namespace std;

#define TURNING_ANGLE -6
#define OTHER_TURNING_ANGLE 6
#define CC_FAST -25
#define OTHER_FAST 25

fanboat_ll::fanboatLL fll;
float lastDistance = 1000.0;
int lastX = 1000;
int lastY = 1000;
bool go, done;
int targetYaw = 1000;

class CameraServo{
public:
  CameraServo();
private:
  void msgCallback(const lab3::ballLandInfo::ConstPtr& msg);
  void fanboatLL_callback(const fanboat_ll::fanboatLL::ConstPtr& ang);

  ros::NodeHandle nh;

  //Subscriber for landmark
  ros::Subscriber img_arb_sub_;
  ros::Subscriber fanboatLL_sub_;

  //Publisher for angle
  ros::Publisher angle_pub_;
};

CameraServo::CameraServo()
{
  img_arb_sub_ = nh.subscribe("ballLandInfo", 1, &CameraServo::msgCallback, this);
  go = false;
  done = false;
  //Landmark position publisher
  angle_pub_ = nh.advertise<lab2::angle_msg>("angle_cam",1);

  //Subscribe to arbitated angle messages                                                                                                     
  fanboatLL_sub_ =  nh.subscribe<fanboat_ll::fanboatLL>("sensors", 1, &CameraServo::fanboatLL_callback, this);
}

bool CCdirection = false;
int state = 0;
int fastCount = 0;
void CameraServo::msgCallback(const lab3::ballLandInfo::ConstPtr& msg)
{
  if(go && !done) {
    int x = msg->x;
    int y = msg->y;
    float distance = msg->distance;

	double diffang = 0.0;
	//tracking ball
	if(msg->type && distance<450 && distance > 0){
		diffang = (x/300.0) * 22.5;
	  ROS_INFO("I see the ball!");
	  state = 1;
	  fastCount = 0;
	  targetYaw = fll.yaw;
	}
	//else if (msg->type && ((abs(lastX) < 200 && abs(lastX) > 20) || lastY < -80)) //Go straight - ball is in range
  //{
	 // diffang = 0.0;
	  //x = lastX;
	  //y = lastY;
//	  distance = lastDistance;
//	  ROS_INFO("Go straight");
//	}
	else if (msg->type)
	{ //trying to find the ball/landmark
		x = 1000;
		if(state == 1) {
		  CCdirection = !CCdirection;
		}
		if(CCdirection) {
		  diffang = TURNING_ANGLE;
		  if(fastCount++ < 16) {
		    diffang = CC_FAST;
		  }
		} else {
		  diffang = OTHER_TURNING_ANGLE;
		  if(fastCount++ < 16) {
		    diffang = OTHER_FAST;
		  }
		}
		state = 0;
		//		if(targetYaw < 1000) {
		//  diffang = targetYaw;
		//}
	  ROS_INFO("Where is the ball?!");
	  state = 0;
	}
	else if (msg->type == false && distance <300 && distance > 0){
		if(distance > 100){
			diffang = (x/300.0) * 22.5;
			ROS_INFO("Chasing down the landmark!");
			state = 1;
		}
		else{
			done = true;
		}
	}
	else if (msg->type == false){
		diffang = TURNING_ANGLE;
		x = 1000;
	  ROS_INFO("Where is the landmark?!");
	  if(state == 1) {
	    CCdirection = !CCdirection;
	  }
	  if(CCdirection) {
	    diffang = TURNING_ANGLE;
	    if(fastCount++ < 16) {
	      diffang = CC_FAST;
	    }
	  } else {
	    diffang = OTHER_TURNING_ANGLE;
	    if(fastCount++ < 16) {
	      diffang = OTHER_FAST;
	    }
	  }

	}
	lastX = x;
	lastY = y;
	lastDistance = distance;
	//if(msg->type && targetYaw == 1000) {
	  diffang += fll.yaw;
	  //}
  diffang = (diffang > 180) ? diffang - 360 : ((diffang <= -180) ? diffang + 360 : diffang);
	
	lab2::angle_msg ang;
	ang.thrust = .32;
	ang.angle = diffang;
 	 angle_pub_.publish(ang);
  }
}

//Get feedback from fanboat                                                                                                                         
void CameraServo::fanboatLL_callback(const fanboat_ll::fanboatLL::ConstPtr& f_ll)
{
  fll = *f_ll;
  go = true;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "CameraServo");
  CameraServo ls;
  ros::spin();
  return 0;
}
