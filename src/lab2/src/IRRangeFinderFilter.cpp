#include <ros/ros.h>
#include <lab2/angle_msg.h>
#include <fanboat_ll/fanboatMotors.h>
#include <fanboat_ll/fanboatLL.h>
#include <math.h>
#include <queue>
#include <algorithm>

class IRRangeFinderFilter
{
public:
	IRRangeFinderFilter();

	//Private functions/variables
private:
	void fanboatLL_callback(const fanboat_ll::fanboatLL::ConstPtr& ang);

	ros::NodeHandle nh_;

	ros::Subscriber fanboatLL_sub_;
};

IRRangeFinderFilter::IRRangeFinderFilter()
{
	//Subscribe to arbitated angle messages
	fanboatLL_sub_ =  nh_.subscribe<fanboat_ll::fanboatLL>("fanboatLL", 1, &IRRangeFinderFilter::fanboatLL_callback, this);


	sensors_pub_ = nh_.advertise<lab2::sensor_msg>("motors", 1);



}

//Variables
fanboat_ll::fanboatLL fll;
double left,right;
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
void IRRangeFinderFilter::fanboatLL_callback(const fanboat_ll::fanboatLL::ConstPtr& f_ll)
{
	fll = *f_ll;
	left = filter(fll.a0, &leftq);
	right = filter(fll.a1, &rightq);

	ROS_INFO("a0 = %d, left = %f, a1 = %d, right = %f",fll.a0,left,fll.a1,right);
}

int main(int argc, char** argv)
{

	ros::init(argc, argv, "IRRangeFinderFilter");
	IRRangeFinderFilter IRRangeFinderFilter;

	ros::spin();
}
