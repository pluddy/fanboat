#include <ros/ros.h>
#include <fanboat_ll/fanboatLL.h>

bool isYawValid;
double yaw = 0;
double offset = 0;

class yawSync
{
public:
  yawSync();
  ros::Publisher angle_tri_pub_;

//private variables that can be accessed in callback
private:
  void fanboatLL_callback(const fanboat_ll::fanboatLL::ConstPtr& fll);
  ros::NodeHandle nh_;
  ros::Subscriber fll_sub_;
  ros::Publisher yaw_pub_;
};

//setting up the button variables
yawSync::yawSync()
{
  fll_sub_ =  nh_.subscribe<fanboat_ll::fanboatLL>("fanboatLL", 1, &yawSync::fanboatLL_callback, this);
  yaw_pub_ = nh_.advertise<fanboat_ll::fanboatLL>("fll_sync", 1);
}


void yawSync::fanboatLL_callback(const fanboat_ll::fanboatLL::ConstPtr& fll)
{
	fanboat_ll::fanboatLL fll_sync = *fll;
	yaw = fll->yaw - 360;
	if(!isYawValid) {
		isYawValid = true;
		offset = -yaw;
		ROS_INFO("offset = %f ", offset);
	}
	
	yaw += offset; //Center it so the initial yaw is 0, and all other angles are relative;
	yaw = (yaw > 180) ? yaw-360 : (yaw <= -180)? yaw + 360 : yaw; //(-180,180]
	
	fll_sync.yaw = yaw;
	ROS_INFO("yaw = %f", yaw);
	yaw_pub_.publish(fll_sync);
}



int main(int argc, char** argv)
{
    ros::init(argc, argv, "yawSync");
    yawSync yawSync;
    ros::spin();
}
