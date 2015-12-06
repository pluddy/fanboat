#include <ros/ros.h>
#include <lab2/angle_msg.h>
#include <lab3/ballLandInfo.h>
#include <fanboat_ll/fanboatMotors.h>
#include <fanboat_ll/fanboatLL.h>
#include <math.h>
#include <project/rocket_msg.h>
using namespace std;

class rocket_controller{
public:
  rocket_controller();
private:
  void msgCallback(const lab3::ballLandInfo::ConstPtr& msg);

  ros::NodeHandle nh;

  //Subscriber for landmark
  ros::Subscriber img_arb_sub_;

  //Publisher for angle
  ros::Publisher angle_pub_;
  ros::Publisher rocket_pub_;
};

rocket_controller::rocket_controller()
{
  img_arb_sub_ = nh.subscribe("ballLandInfo", 1, &rocket_controller::msgCallback, this);

  //Landmark position publisher
  angle_pub_ = nh.advertise<lab2::angle_msg>("angle_cam",1);

  rocket_pub_ = nh.advertise<project::rocket_msg>("rocket_command",1);
}

void rocket_controller::msgCallback(const lab3::ballLandInfo::ConstPtr& msg)
{
	int x = msg->x;
	int y = msg->y;
	float distance = msg->distance;

	int diffx = 300 - x;
  double diffang = (diffx/300.0) * 22.5;

	project::rocket_msg rocket;
	rocket.angle = diffang;
	//ang.thrust = 0.3;
  rocket_pub_.publish(rocket);
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "rocket_controller");
  rocket_controller rc;
  ros::spin();
  return 0;
}
