#include <ros/ros.h>
#include <lab3/ballLandInfo.h>
#include <ball_detector/ballLocation.h>
#include <math.h>
class ballConstant
{
public:
	ballConstant();

private:
	void ballCallback(const ball_detector::ballLocation::ConstPtr& land);


	ros::NodeHandle nh_;
	ros::Subscriber ball_sub_;

};

//all the buttons/axis that we used
ballConstant::ballConstant()
{
	ball_sub_ =  nh_.subscribe<ball_detector::ballLocation>("ballLocation", 1, &ballConstant::ballCallback, this);
}

ball_detector::ballLocation ball_values;
//callback/interrupt
void ballConstant::ballCallback(const ball_detector::ballLocation::ConstPtr& ball)
{
	ball_values = *ball;
}

int main(int argc, char** argv)
{	
	ros::init(argc, argv, "ballConstant");
	ballConstant ballConstant;
	ros::Rate loop_rate(13);//set frequency to 13Hz
	ros::NodeHandle nh;
	ros::Publisher pub = nh.advertise<ball_detector::ballLocation>("ballConstant", 1);//publisher

	//Continually publish the latest joy messages to ballConstant
	while(ros::ok()) {
	  ball_values.header.stamp = ros::Time::now();
		pub.publish(ball_values);

		ros::spinOnce();//spin
		loop_rate.sleep();
	}
	ros::spin();
}

