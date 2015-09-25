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

//private variables that can be accessed in callback
private:
  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);
  ros::NodeHandle nh_;
  double x_, y_;
  int lb_, dup_, ddown_, rb_;
  double l_scale_, a_scale_;
  ros::Subscriber joy_sub_;
};

//setting up the button variables
xboxjoy::xboxjoy():
  x_(0),
  y_(1),
  lb_(4),
  rb_(5),
  dup_(13),
  ddown_(14)
{

  joy_sub_ =  nh_.subscribe<sensor_msgs::Joy>("joy", 1, &xboxjoy::joyCallback, this);
  
}

//global variables that can be passed from callback to main
int i = 0;
double left, right;
bool on = false;
bool done = false;
bool iterationDone = false;
int countIterations = 0;

void xboxjoy::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
  if(joy->buttons[lb_] == true) on = !on;
  
  if(on == true && !done){//forward
    left = 0.36; 
    right = 0.277;
  }
  else if (!done){//idle
    left = .30;
    right = .22;
  }
  else{//off
    left = 0;
    right = 0;
  }
}


double totalDistance = 1;
bool firstTimeZero = false;

int main(int argc, char** argv)
{
  
    ros::init(argc, argv, "xboxjoy");
    xboxjoy xboxjoy;
    fanboat_ll::fanboatMotors boat;
    ros::Rate loop_rate(12);//sets the f to 12Hz
    ros::NodeHandle nh;
    ros::Publisher vel_pub = nh.advertise<fanboat_ll::fanboatMotors>("motors", 1);
    done = false;
    i = 0;
    int j = 0;
    double pubs = 9;
    double iterations = totalDistance /.5;//iterations is how many times it will go .5m
    while(ros::ok()) {
      j =0;
      while(!on && ros::ok()){
        boat.left = left;
        boat.right = right;
        vel_pub.publish(boat);
        ros::spinOnce();
        loop_rate.sleep();
        ROS_INFO("left: %f right: %f on: %d j = %d iterations = %lf !on",left,right, on, j, iterations);//idle
      }
      while(!done && on && ros::ok()){//going forward
        if(iterations < 1)//if you get something like 1.3m
          pubs = pubs*iterations;
        for (j = 0; j < pubs && ros::ok() && on; j++ ){//1 iteration
          boat.left = left;
          boat.right = right;
          vel_pub.publish(boat);//goes forward
          ros::spinOnce();
          loop_rate.sleep();
          ROS_INFO("left: %f right: %f on: %d j = %d iterations = %lf for",left,right, on, j, iterations);
        }
        iterations = iterations - 1;//minus the iterations
        if (iterations <= 0.05)
          done = true;
        usleep(540000);//sleep so that you dont go too fast between iterations
      }
      j = 0;
      left = 0.30;
      right = .22;//idle
    
    ROS_INFO("left: %f right: %f on: %d j = %d iterations = %lf spin",left,right, on, j, iterations);
    ros::spinOnce();
    loop_rate.sleep();
    }  
    ros::spin()
}
