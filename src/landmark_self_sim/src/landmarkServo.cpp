#include <ros/ros.h>
#include <landmark_self_sim/landmarkLocation.h>
#include <lab2/angle_msg.h>
#include <fanboat_ll/fanboatMotors.h>
#include <fanboat_ll/fanboatLL.h>
#include <math.h>
using namespace std;

class LandmarkServo{
public:
  LandmarkServo();
private:
  void landmarkCallback(const landmark_self_sim::landmarkLocation::ConstPtr& msg);

  ros::NodeHandle nh;

  //Subscriber for landmark
  ros::Subscriber landmark_sub_;

  //Publisher for angle
  ros::Publisher angle_pub_;
};

LandmarkServo::LandmarkServo()
{
  landmark_sub_ = nh.subscribe("landmarkLocation", 1, &LandmarkServo::landmarkCallback, this);

  //Landmark position publisher
  angle_pub_ = nh.advertise<lab2::angle_msg>("servoAngle",1);
}

void LandmarkServo::landmarkCallback(const landmark_self_sim::landmarkLocation::ConstPtr& msg)
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

  ROS_INFO("angle: %f", diffang);
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "landmarkServo");
  LandmarkServo ls;
  ros::spin();
  return 0;
}
