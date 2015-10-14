#include <ros/ros.h>
#include <lab2/angle_msg.h>
#include <fanboat_ll/fanboatMotors.h>
#include <fanboat_ll/fanboatLL.h>
#include <math.h>
#include <queue>
#include <algorithm>

class sensorFilter
{
public:
	sensorFilter();

	//Private functions/variables
private:
	void fanboatLL_callback(const fanboat_ll::fanboatLL::ConstPtr& ang);

	ros::NodeHandle nh_;

	ros::Subscriber fanboatLL_sub_;
	ros::Publisher sensors_pub_;
};

sensorFilter::sensorFilter()
{
	//Subscribe to arbitated angle messages
	fanboatLL_sub_ =  nh_.subscribe<fanboat_ll::fanboatLL>("fanboatLL", 1, &sensorFilter::fanboatLL_callback, this);
	sensors_pub_ = nh_.advertise<fanboat_ll::fanboatLL>("sensors", 1);
}

//Variables
fanboat_ll::fanboatLL fll;
double left,right;
double yaw = 0, offset = 0;
bool isYawValid = false;

std::queue<double> leftq;
std::queue<double> rightq;

double filter(double input, std::queue<double> *q)
{
	q->push(input);
	if(q->size() > 3){
		q->pop();
	}

	std::queue<double> cpq = *q;
	double cparr[3];
	for(int i = 0; i < q->size(); i++) {
		cparr[i] = cpq.front();
		cpq.pop();
	}
	std::sort(cparr,cparr + 3);

	return cparr[0];
}

//Get feedback from fanboat
void sensorFilter::fanboatLL_callback(const fanboat_ll::fanboatLL::ConstPtr& f_ll)
{
	fll = *f_ll;
	left = filter(fll.a0, &leftq);
	right = filter(fll.a1, &rightq);

	yaw = fll.yaw - 360;
		if(!isYawValid) {
			isYawValid = true;
			offset = -yaw;
			ROS_INFO("offset = %f ", offset);
		}

	yaw += offset; //Center it so the initial yaw is 0, and all other angles are relative;
	yaw = (yaw > 180) ? yaw-360 : (yaw <= -180)? yaw + 360 : yaw; //(-180,180]

	fll.a0 = left;
	fll.a1 = right;
	fll.yaw = yaw;

	sensors_pub_.publish(fll);
	ROS_INFO("yaw = %f, a0 = %d, left = %f, a1 = %d, right = %f",yaw, fll.a0,left,fll.a1,right);
}

int main(int argc, char** argv)
{

	ros::init(argc, argv, "sensorFilter");
	sensorFilter sensorFilter;

	ros::spin();
}
