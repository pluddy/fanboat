#include <ros/ros.h>
#include <math.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/Vector3.h>
#include <lab3/hasBall.h>
#include <project/rocket_msg.h>

class VisualArbitrator
{
public:
	VisualArbitrator();
	~VisualArbitrator(){};

	//Private functions/variables
private:

	void imageCb(const sensor_msgs::ImageConstPtr& msg);
	void has_ball_callback(const project::rocket_msg::ConstPtr& msg);

	ros::NodeHandle nh_;
	image_transport::ImageTransport it;
	image_transport::Subscriber image_sub_;

	ros::Subscriber defensive_sub_;
	image_transport::Publisher ball_img_pub_;
	image_transport::Publisher land_img_pub_;
};

//Set values to read from xbox controller
VisualArbitrator::VisualArbitrator() :it(nh_)
{
	image_sub_ = it.subscribe("/usb_cam/image_raw", 1, &VisualArbitrator::imageCb, this);
	defensive_sub_ = nh_.subscribe("/launcher_topic", 1, &VisualArbitrator::has_ball_callback, this);

	land_img_pub_ = it.advertise("usb_cam/image_raw_land", 3);
	ball_img_pub_ = it.advertise("usb_cam/image_raw_ball", 3);
}

bool lookForBall = true;
void VisualArbitrator::imageCb(const sensor_msgs::ImageConstPtr& image){
	if(lookForBall){
		ball_img_pub_.publish(*image);
	}
	else{
		land_img_pub_.publish(*image);
	}
}

//If we don't have the ball, look for it
void VisualArbitrator::has_ball_callback(const project::rocket_msg::ConstPtr& msg)
{
	if(msg->state > 0)
  		lookForBall = false;
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "visualArbitrator");
	VisualArbitrator visualArbitrator;

	ros::spin();
}
