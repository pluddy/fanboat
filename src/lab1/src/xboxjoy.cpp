// %Tag(FULL)%
// %Tag(INCLUDE)%
#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Twist.h>
#include <fanboat_ll/fanboatMotors.h>
// %EndTag(INCLUDE)%
// %Tag(CLASSDEF)%
class xboxjoy
{
public:
  xboxjoy();

private:
  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);
  
  ros::NodeHandle nh_;

  int left_, right_;
  double l_scale_, a_scale_;
  ros::Publisher vel_pub_;
  ros::Subscriber joy_sub_;
  
};
// %EndTag(CLASSDEF)%
// %Tag(PARAMS)%
xboxjoy::xboxjoy():
  left_(2),
  right_(5)
{

//  nh_.param("axis_linear", linear_, linear_);
//  nh_.param("axis_angular", angular_, angular_);
//  nh_.param("scale_angular", a_scale_, a_scale_);
//  nh_.param("scale_linear", l_scale_, l_scale_);
// %EndTag(PARAMS)%
// %Tag(PUB)%
  vel_pub_ = nh_.advertise<fanboat_ll::fanboatMotors>("motors", 1);
// %EndTag(PUB)%
// %Tag(SUB)%
  joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &xboxjoy::joyCallback, this);
// %EndTag(SUB)%
}
// %Tag(CALLBACK)%
void xboxjoy::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
  fanboat_ll::fanboatMotors boat;
  double r = joy->axes[right_];
  double l = joy->axes[left_];
  ROS_INFO("%f %f",l,r);
  r = (1 - r) / 2;
  l = (1 - l) / 2;
  boat.left = l;
  boat.right = r;
  ROS_INFO("%f %f",l,r);
  vel_pub_.publish(boat);
}
// %EndTag(CALLBACK)%
// %Tag(MAIN)%
int main(int argc, char** argv)
{
  ros::init(argc, argv, "xboxjoy");
  xboxjoy xboxjoy;

  ros::spin();
}
// %EndTag(MAIN)%
// %EndTag(FULL)%
