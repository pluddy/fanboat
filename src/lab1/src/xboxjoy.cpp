#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Twist.h>
#include <fanboat_ll/fanboatMotors.h>
#include <math.h>
class xboxjoy
{
public:
  xboxjoy();

//private variables that can be used in joy callback
private:
  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);
  
  ros::NodeHandle nh_;

  double x_, y_;
  int lb_, dup_, ddown_;
  double l_scale_, a_scale_;
  ros::Subscriber joy_sub_;
  
};

//all the buttons/axis that we used
xboxjoy::xboxjoy():
  x_(0),
  y_(1),
  lb_(4),
  dup_(13),
  ddown_(14)
{

  joy_sub_ =  nh_.subscribe<sensor_msgs::Joy>("joy", 1, &xboxjoy::joyCallback, this);
  

}
double left, right;
bool on = false;
bool timed = false;

//callback/interrupt
void xboxjoy::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
  timed = false;
  bool dup = joy->buttons[dup_];
  bool ddown = joy->buttons[ddown_];
  if(joy->buttons[lb_] == true) on = !on;
  
  if(on == true){
    if(dup == true){//up dpad goes forward
      left = .29;
      right = .289;
    }
    else if (ddown == true){//testing stuff with the set distance
      left = .30;
      right = .28;
      timed = true;
    }
    else{//normal joystick use
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
  }
}

bool firstTimeZero = false;
int main(int argc, char** argv)
{
  
    ros::init(argc, argv, "xboxjoy");
    xboxjoy xboxjoy;
    fanboat_ll::fanboatMotors boat;
    ros::Rate loop_rate(13);//set frequency to 13Hz
    ros::NodeHandle nh;
    ros::Publisher vel_pub = nh.advertise<fanboat_ll::fanboatMotors>("motors", 1);//publisher
    bool done = false;
    int i = 0;
    //on off button is left bumper so that we can control when motors are moving
    while(ros::ok() && !done) {
      if (on == true){     
        boat.left = left;
        boat.right = right;
        ROS_INFO("left: %f right: %f on: %d i = %d",left,right, on, i);
        vel_pub.publish(boat);
      }
      else{//motors off
        boat.left = 0;
        boat.right = 0;
        ROS_INFO("left: %f right: %f on: %d i = %d",left,right, on, i);
        vel_pub.publish(boat);
      }
      ros::spinOnce();//spin
      loop_rate.sleep();
      if(timed){//more timing stuff not used really
        i++;
        if(i >= 45) {
          done = true;
        }
      } 
    } 
    ros::spin();
  }

