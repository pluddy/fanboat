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
  int lb_, dup_, ddown_, rb_;
  double l_scale_, a_scale_;
  //ros::Publisher vel_pub_;
  ros::Subscriber joy_sub_;
  
};
// %EndTag(CLASSDEF)%
// %Tag(PARAMS)%
xboxjoy::xboxjoy():
  x_(0),
  y_(1),
  lb_(4),
  rb_(5),
  dup_(13),
  ddown_(14)
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
int i = 0;
double left, right;
bool on = false;
bool done = false;
bool timed = false;
// %Tag(CALLBACK)%
void xboxjoy::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
  timed = false;
  bool dup = joy->buttons[dup_];
  bool ddown = joy->buttons[ddown_];
  if(joy->buttons[lb_] == true) on = !on;
  if(joy->buttons[rb_] == true) done = !done;
  
  if(on == true){
    if(dup == true){
      left = .29;
      right = .289;
    }
    else if (ddown == true){
      left = .353;
      right = .29;
      timed = true;
    }
    else{
      left = 0.34; 
      right = 0.28;
      i =0;
    }
  }



  
  
  
}
// %EndTag(CALLBACK)%
int pubs = 19;
double meters = .5;
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
    done = false;
    i = 0;
    int j = 0;

    while(ros::ok()) {
      if (on == true && !done){     
        boat.left = left;
        boat.right = right;
	
        if (j < 10) {
          boat.left += .05;
          boat.right += .045;
          j++;
        }
        ROS_INFO("left: %f right: %f on: %d i = %d",left,right, on, i);
        vel_pub.publish(boat);
      }
      else{
        boat.left = 0;
        boat.right = 0;
        j = 0;
        ROS_INFO("left: %f right: %f on: %d i = %d",left,right, on, i);
        vel_pub.publish(boat);
      }
      ros::spinOnce();
      loop_rate.sleep();
      if(timed && !done){
        i++;
        if(i >= meters *1.13 * pubs) {
          done = true;
          i = 0;
          timed = false;
        }
      } 
    } 
    ros::spin();
  }

// %EndTag(MAIN)%
// %EndTag(FULL)%