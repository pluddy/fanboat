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
  int lb_;
  double l_scale_, a_scale_;
  //ros::Publisher vel_pub_;
  ros::Subscriber joy_sub_;
  
};
// %EndTag(CLASSDEF)%
// %Tag(PARAMS)%
xboxjoy::xboxjoy():
  x_(0),
  y_(1),
  lb_(4)
{

//  nh_.param("axis_linear", linear_, linear_);
//  nh_.param("axis_angular", angular_, angular_);
//  nh_.param("scale_angular", a_scale_, a_scale_);
//  nh_.param("scale_linear", l_scale_, l_scale_);
// %EndTag(PARAMS)%
// %Tag(PUB)%
  //vel_pub_ = nh_.advertise<fanboat_ll::fanboatMotors>("motors", 1);
// %EndTag(PUB)%
// %Tag(SUB)%
  joy_sub_ =  nh_.subscribe<sensor_msgs::Joy>("joy", 1, &xboxjoy::joyCallback, this);
  
// %EndTag(SUB)%
}
double left, right;
bool on = false;
// %Tag(CALLBACK)%
void xboxjoy::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
  if(joy->buttons[lb_] == true) on = !on;

  if(on == true){
    double x = joy->axes[x_];
    double y = joy->axes[y_];
    left = 0.15; 
    right = 0.15;
    if(y >= 0){
      double thrust = sqrt(x*x + y*y);
      if (thrust > 1) thrust = 1;
      //thrust = thrust *.5 + .5;
      if(x>0){
        right = thrust;
        left = (1 - x)*thrust;
      }
      else{
        left = thrust;
        right = (1 +x)*thrust;
      }
    }
    if(left < .15) left = .15;
    if(right < .15) right = .15;\
  }



  
  
  
}
// %EndTag(CALLBACK)%
// %Tag(MAIN)%
bool firstTimeZero = false;
int main(int argc, char** argv)
{
  
    ros::init(argc, argv, "xboxjoy");
    xboxjoy xboxjoy;
    fanboat_ll::fanboatMotors boat;
    ros::Rate loop_rate(13);
    ros::NodeHandle nh;
    ros::Publisher vel_pub = nh.advertise<fanboat_ll::fanboatMotors>("motors", 1);

    while(ros::ok()) {
      if (on == true){     
        boat.left = left;
        boat.right = right;
        ROS_INFO("left: %f right: %f on: %d",left,right, on);
        vel_pub.publish(boat);
      }
      else{
        boat.left = 0;
        boat.right = 0;
        ROS_INFO("left: %f right: %f on: %d",left,right, on);
        vel_pub.publish(boat);
      }
      ros::spinOnce();
      loop_rate.sleep();
    } 
    ros::spin();
  }

// %EndTag(MAIN)%
// %EndTag(FULL)%
