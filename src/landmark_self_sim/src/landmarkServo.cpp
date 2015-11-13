#include <ros/ros.h>
#include <landmark_self_sim/landmarkLocation.h>
#include <lab2/angle_msg.h>
#include <fanboat_ll/fanboatMotors.h>
#include <fanboat_ll/fanboatLL.h>
#include <math.h>
using namespace std;

class CameraServo{
public:
  CameraServo();
private:
  void imgCallback(const landmark_self_sim::landmarkLocation::ConstPtr& msg);

  ros::NodeHandle nh;

  //Subscriber for landmark
  ros::Subscriber img_arb_sub_;

  //Publisher for angle
  ros::Publisher angle_pub_;
};

CameraServo::CameraServo()
{
  img_arb_sub_ = nh.subscribe("img_arb", 1, &CameraServo::imgCallback, this);

  //Landmark position publisher
  angle_pub_ = nh.advertise<lab2::angle_msg>("CameraServoAngle",1);
}

void CameraServo::imgCallback(const lab3::ballLandInfo::ConstPtr& msg)
{
	int xtop = msg->xtop;
	int ytop = msg->ytop;
	int xbottom = msg->xbottom;
	int ybottom = msg->ybottom;
  int height = msg->height;

  int width = (11/8.5)*height;

	int x = ((xtop + xbottom)/2) - width/2;

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
