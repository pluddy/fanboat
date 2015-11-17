#include <ros/ros.h>
#include <landmark_self_sim/landmarkLocation.h>
#include <lab2/angle_msg.h>
#include <lab3/ballLandInfo.h>
#include <fanboat_ll/fanboatMotors.h>
#include <fanboat_ll/fanboatLL.h>
#include <math.h>
using namespace std;

class CameraServo{
public:
  CameraServo();
private:
  void msgCallback(const lab3::ballLandInfo::ConstPtr& msg);

  ros::NodeHandle nh;

  //Subscriber for landmark
  ros::Subscriber img_arb_sub_;

  //Publisher for angle
  ros::Publisher angle_pub_;
};

CameraServo::CameraServo()
{
  img_arb_sub_ = nh.subscribe("ballLandInfo", 1, &CameraServo::msgCallback, this);

  //Landmark position publisher
  angle_pub_ = nh.advertise<lab2::angle_msg>("angle_cam",1);
}

void CameraServo::msgCallback(const lab3::ballLandInfo::ConstPtr& msg)
{
	int x = msg->x;
	int y = msg->y;
	float distance = msg->distance;

	int diffx = 300 - x;
  double diffang = (diffx/300.0) * 22.5;

	lab2::angle_msg ang;
	ang.angle = diffang;
	ang.thrust = 0.3;
  angle_pub_.publish(ang);
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "CameraServo");
  CameraServo ls;
  ros::spin();
  return 0;
}
