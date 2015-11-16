#include <ros/ros.h>
#include <math.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/Vector3.h>
#include <std_msgs/Bool.h>

class VisualArbitrator
{
public:
	VisualArbitrator();
	~VisualArbitrator(){};

	//Private functions/variables
private:

	void imageCb(const sensor_msgs::ImageConstPtr& msg);
//	void has_ball_callback(const std_msgs::Bool::ConstPtr& msg);



	ros::NodeHandle nh_;
	image_transport::ImageTransport it;
	image_transport::Subscriber image_sub_;
//	ros::Subscriber has_ball_sub_;
	image_transport::Publisher ball_img_pub_;
  image_transport::Publisher land_img_pub_;

};

//Set values to read from xbox controller
VisualArbitrator::VisualArbitrator()
:it(nh_)
	{
		//Subscribe to joy_constant for button controls to arbitrate
  	image_sub_ = it.subscribe("/usb_cam/image_raw", 1, &VisualArbitrator::imageCb, this);
		//has_ball_sub_ = nh_.subscribe("hasBall", 1, &visualArbitrator::has_ball_callback, this);
		image_transport::Publisher land_img_pub_ = it.advertise("/usb_cam/image_raw_land", 3);
 		image_transport::Publisher ball_img_pub_ = it.advertise("/usb_cam/image_raw_ball", 3);
	//	ball_img_pub_ = it.advertise<sensor_msgs::Image>("/usb_cam/image_raw_ball", 10);
		//land_img_pub_ = it.advertise<sensor_msgs::Image>("/usb_cam/image_raw_landmark", 1);
	}

	bool lookForBall = true;
	void VisualArbitrator::imageCb(const sensor_msgs::ImageConstPtr& msg){
		if(lookForBall == true){
			ball_img_pub_.publish(msg);
		}
		else{
			land_img_pub_.publish(msg);
		}
	}

int main(int argc, char** argv)
{

	ros::init(argc, argv, "visualArbitrator");
	VisualArbitrator visualArbitrator;

	ros::spin();
}
