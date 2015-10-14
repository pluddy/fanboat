#include <ros/ros.h>
#include <lab2/angle_msg.h>
#include <fanboat_ll/fanboatMotors.h>
#include <fanboat_ll/fanboatLL.h>
#include <math.h>

class reactiveControl
{
public:
	reactiveControl();
	
	//Private functions/variables
private:
	//void angle_callback(const lab2::angle_msg::ConstPtr& ang);
	void fanboatLL_callback(const fanboat_ll::fanboatLL::ConstPtr& ang);

	ros::NodeHandle nh_;

	ros::Publisher angles_pub_;

	ros::Subscriber sensors_sub_;
	
};

double pValue;
double dValue;
double rightScale;
double leftScale;
reactiveControl::reactiveControl()
{
	//Subscribe to arbitated angle messages
	sensors_sub_ = nh_.subscribe<fanboat_ll::fanboatLL>("sensors", 1, &reactiveControl::fanboatLL_callback, this);


	//Publish to angles topic
	angles_pub_ = nh_.advertise<lab2::angle_msg>("angle_rc", 1);

}

//Variables
fanboat_ll::fanboatLL fll;
uint16_t initLeftS = -100;
uint16_t initRightS = -100;
double angle, thrust;
double init = -1000;

//pulled from the arduino library.
double map(double x, double in_min, double in_max, double out_min, double out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void reactive(int leftSensor, int rightSensor)
{
	//right = .0;
	//left = .0;

	ROS_INFO("leftS = %d rightS = %d",leftSensor,rightSensor);
}



//Get feedback from fanboat
void reactiveControl::fanboatLL_callback(const fanboat_ll::fanboatLL::ConstPtr& f_ll)
{
	lab2::angle_msg msg;
	uint16_t leftS;
	uint16_t rightS;
	leftS = fll.a0;
	rightS = fll.a0;
	if (initLeftS == -100){
		initLeftS = leftS;
	}
	if (initRightS == -100){
		initRightS = rightS;
	}
	reactive(leftS,rightS);
	msg.angle = 0.0;
	msg.thrust = .3;
	//motors_pub_.publish(boat);
}

int main(int argc, char** argv)
{
	
	ros::init(argc, argv, "reactiveControl");
	reactiveControl reactiveControl;

	ros::spin();
}
