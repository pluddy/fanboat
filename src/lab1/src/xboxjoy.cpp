// %Tag(FULL)%
// %Tag(INCLUDE)%
#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Twist.h>
#include <fanboat_ll/fanboatMotors.h>
#include <math.h>
// %EndTag(INCLUDE)%
// %Tag(CLASSDEF)%
class xboxjoy
{
public:
  xboxjoy();

private:
  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);
  
  ros::NodeHandle nh_;

  double x_, y_;
  double l_scale_, a_scale_;
  ros::Publisher vel_pub_;
  ros::Subscriber joy_sub_;
  
};
// %EndTag(CLASSDEF)%
// %Tag(PARAMS)%
xboxjoy::xboxjoy():
  x_(0),
  y_(1)
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
  joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 1, &xboxjoy::joyCallback, this);
// %EndTag(SUB)%
}
// %Tag(CALLBACK)%
void xboxjoy::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
  fanboat_ll::fanboatMotors boat;
  double x = joy->axes[x_];
  double y = joy->axes[y_];
  double left = 0, right = 0;
  if(y > 0){
    double thrust   = sqrt(x*x + y*y);
    if(x>0){
      right = thrust;
      left = (1 - x)*thrust;
    }
    else{
      left = thrust;
      right = (1 +x)*thrust;
    }
    //double proportionr = (x+ 1)/2;
    //double proportionl = 1-proportionr;
    //left = thrust*proportionl;
    //right = thrust*proportionr; 
  }


  boat.left = left;
  boat.right = right;
  ROS_INFO("left: %f right: %f",left,right);
  
  ros::Rate loop_rate(16);
  loop_rate.sleep();
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
