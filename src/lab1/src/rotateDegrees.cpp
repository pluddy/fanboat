#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Twist.h>
#include <fanboat_ll/fanboatMotors.h>
#include <fanboat_ll/fanboatLL.h>
#include <math.h>

class xboxjoy
{
public:
  xboxjoy();

//Private functions/variables
private:
  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);
  void fanboatLLCallback(const fanboat_ll::fanboatLL::ConstPtr& fll);

  ros::NodeHandle nh_;
  double x_, y_;
  int lb_, rb_, dup_, ddown_;
  double l_scale_, a_scale_;
  //ros::Publisher vel_pub_;
  ros::Subscriber joy_sub_;
  ros::Subscriber fanboatLL_sub_;
};

//Set values to read from xbox controller
xboxjoy::xboxjoy():
  x_(0),
  y_(1),
  lb_(4),
  rb_(5),
  dup_(13),
  ddown_(14)
{
  //Subscribe to joy and fanboatLL
  joy_sub_ =  nh_.subscribe<sensor_msgs::Joy>("joy", 1, &xboxjoy::joyCallback, this);
  fanboatLL_sub_ = nh_.subscribe<fanboat_ll::fanboatLL>("fanboatLL", 1, &xboxjoy::fanboatLLCallback, this);
}

//Variables to communicate left/right motor power and current/final yaw values
int i = 0;
double left, right;
bool on = false;
bool done = false;
bool timed = false;
double initYaw = -1;
double yaw = 0;
int destDegrees;
double degreesToSpin = -90;

//Update the yaw - if it is the first time, set the initial yaw and calculate end yaw
void xboxjoy::fanboatLLCallback(const fanboat_ll::fanboatLL::ConstPtr& fll)
{ 
  yaw = fll->yaw - 180;
  if(initYaw < 0) {
    initYaw = yaw;
    destDegrees = (int)(initYaw + degreesToSpin + 360) % 360;
  }
}

//Read input from the joystick
void xboxjoy::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
  bool dup = joy->buttons[dup_];
  bool ddown = joy->buttons[ddown_];
  if(joy->buttons[lb_] == true) on = !on;
  if(joy->buttons[rb_] == true) done = !done;
  
  if(on == true) {
    if(dup == true) { //turn right
      left = 1;
      right = 0;
      initYaw = yaw;
    }
    else if (ddown == true) { //turn left
      left = 0;
      right = 1;
      initYaw = yaw;
    }
  } else {
    left = 0;
    right = 0;
  }
}

bool firstTimeZero = false;
double error = 5;
int main(int argc, char** argv)
{
  
    ros::init(argc, argv, "xboxjoy");
    xboxjoy xboxjoy;
    fanboat_ll::fanboatMotors boat;
    ros::Rate loop_rate(13);
    ros::NodeHandle nh;
    ros::Publisher vel_pub = nh.advertise<fanboat_ll::fanboatMotors>("motors", 1);
    done = false;

    while(ros::ok()) {
      //if (on == true && !done) {     
      if(!done) {
        if(degreesToSpin > 0) {  //Turn right    
          boat.left = 0.37;
          boat.right = 0;
        } else { //Turn left
          boat.right = 0.28;
          boat.left = 0;
        }

        ROS_INFO("left: %f right: %f on: %d yaw: %.2f",boat.left,boat.right, on, yaw);
        vel_pub.publish(boat); //Publish the values
      }
      else{
        boat.left = 0; //Stop the boat
        boat.right = 0;

        ROS_INFO("left: %f right: %f on: %d",left,right, on);
        vel_pub.publish(boat);
      }
      ros::spinOnce();
      loop_rate.sleep(); //Wait
      if(!done && (yaw < destDegrees + error && yaw > destDegrees - error) && initYaw >= 0) {
          ROS_INFO("Yaw: %f, destDegrees: %d", yaw, destDegrees);
          done = true; //Reached destination yaw, stop
      }
    } 
    ros::spin();
  }
