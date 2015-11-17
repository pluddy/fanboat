#include <ros/ros.h>
#include <lab3/hasBall.h>
#include <fanboat_ll/fanboatMotors.h>
#include <fanboat_ll/fanboatLL.h>
#include <math.h>

class hasBall
{
public:
	hasBall();
	ros::Publisher hasBall_pub_;

	//Private functions/variables
private:
	void sensorFilter_callback(const fanboat_ll::fanboatLL::ConstPtr& ang);
	ros::NodeHandle nh_;

	ros::Subscriber sensors_sub_;

};

hasBall::hasBall()
{
	//Subscribe to sensor messages
	sensors_sub_ = nh_.subscribe<fanboat_ll::fanboatLL>("sensors", 1, &hasBall::sensorFilter_callback, this);

	//Publish to hasBall topic
	hasBall_pub_ = nh_.advertise<lab3::hasBall>("hasBall", 1);
}

//Variables
fanboat_ll::fanboatLL fll;

//Threshold values for sensors
int leftLow = 400, leftHigh = 550, rightLow = 400, rightHigh = 550;
void hasBall::sensorFilter_callback(const fanboat_ll::fanboatLL::ConstPtr& f_ll)
{
	fll = *f_ll;
	lab3::hasBall hasBall;
	int left = fll.a0;
	int right = fll.a1;
	
	//If outside this range, assume we have the ball
	hasBall.hasBall = (left < leftLow) || (left > leftHigh) || (right < rightLow) || (right > rightHigh);
  ROS_INFO("%s", hasBall.hasBall ? "Find landmark" : "Find ball" );
	hasBall_pub_.publish(hasBall);
}

int main(int argc, char** argv)
{

	ros::init(argc, argv, "hasBall");
	hasBall hasBall;

	ros::spin();
}
