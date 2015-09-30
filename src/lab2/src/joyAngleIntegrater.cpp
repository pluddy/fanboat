#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Twist.h>
#include <fanboat_ll/fanboatMotors.h>
#include <math.h>
class joyAngleIntegrater
{
public:
  joyAngleIntegrater();

//private variables that can be used in joy callback
private:
  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);
  
  ros::NodeHandle nh_;

  double x_, y_;
  int lb_, dup_, ddown_;
  double l_scale_, a_scale_;
  ros::Subscriber joy_sub_;
  ros::Publisher vel_pub;
  fanboat_ll::fanboatMotors boat;
  
};

//all the buttons/axis that we used
joyAngleIntegrater::joyAngleIntegrater():
x_(0),
y_(1),
lb_(4),
dup_(13),
ddown_(14)
{
  joy_sub_ =  nh_.subscribe<sensor_msgs::Joy>("joy_constant", 1, &joyAngleIntegrater::joyCallback, this);
  vel_pub = nh.advertise<fanboat_ll::fanboatMotors>("arbitrator_joy", 1);
}
double left, right;
bool on = false;
bool timed = false;

//callback/interrupt
void joyAngleIntegrater::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
  bool dup = joy->buttons[dup_];
  bool ddown = joy->buttons[ddown_];
  if(joy->buttons[lb_] == true) on = !on;
  
  if(on == true){
    double x = joy->axes[x_];
    double y = joy->axes[y_];
    left = 0.15; 
    right = 0.15;
    if(y >= 0){//algorithm to make it go using joy
      double thrust = sqrt(x*x + y*y);
      if (thrust > 1) thrust = 1;
      thrust = thrust * .4;
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
    if(right < .15) right = .15;
  }
  else {
    left = 0;
    right = 0;
  }

  boat.left = left;
  boat.right = right;
  ROS_INFO("left: %f right: %f",left,right);
  vel_pub.publish(boat);
}

bool firstTimeZero = false;
int main(int argc, char** argv)
{
  ros::init(argc, argv, "joyAngleIntegrater");
  joyAngleIntegrater joyAngleIntegrater;

  ros::spin();
}

