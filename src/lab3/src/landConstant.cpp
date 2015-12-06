#include <ros/ros.h>
#include <lab3/ballLandInfo.h>
#include <landmark_self_sim/landmarkLocation.h>
#include <math.h>

int landmarkCode = -1;

class landConstant
{
public:
	landConstant();

private:
	void landCallback(const landmark_self_sim::landmarkLocation::ConstPtr& land);


	ros::NodeHandle nh_;
	ros::Subscriber land_sub_;
};

//all the buttons/axis that we used
landConstant::landConstant()
{
	land_sub_ =  nh_.subscribe<landmark_self_sim::landmarkLocation>("landmarkLocation", 1, &landConstant::landCallback, this);
	nh_.getParam("landmarkCode", landmarkCode);
}
int count = 0;
landmark_self_sim::landmarkLocation land_values;
//callback/interrupt
void landConstant::landCallback(const landmark_self_sim::landmarkLocation::ConstPtr& land)
{
  if(land->code == landmarkCode) {
    count = 0;
	  land_values = *land;
  }
}

int main(int argc, char** argv)
{	
	ros::init(argc, argv, "landConstant");
	landConstant landConstant;
	ros::Rate loop_rate(10);//set frequency to 13Hz
	ros::NodeHandle nh;
	ros::Publisher pub = nh.advertise<landmark_self_sim::landmarkLocation>("landConstant", 1);//publisher

	//Continually publish the latest joy messages to landConstant
	while(ros::ok()) {
	  land_values.header.stamp = ros::Time::now();
		pub.publish(land_values);
		count ++;
		if (count == 3){
		  land_values.code = -1;
		  land_values.distance = 1000.0;
      count = 0;
    }
		ros::spinOnce();//spin
		loop_rate.sleep();
	}
	ros::spin();
}

