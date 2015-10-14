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
	void sensorFilter_callback(const fanboat_ll::fanboatLL::ConstPtr& ang);
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
	sensors_sub_ = nh_.subscribe<fanboat_ll::fanboatLL>("sensors", 1, &reactiveControl::sensorFilter_callback, this);


	//Publish to angles topic
	angles_pub_ = nh_.advertise<lab2::angle_msg>("angle_rc", 1);

}

//Variables
fanboat_ll::fanboatLL fll;
double initLeftS = -100;
double initRightS = -100;
double init = -1000;
double leftS, rightS, rightMotor, leftMotor, angle, thrust, diffL, diffR;
bool isMapping = false;
bool isForward = true;

//pulled from the arduino library.
double map(double x, double in_min, double in_max, double out_min, double out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void reactive()
{
	diffL = initLeftS - leftS;
	diffR = initRightS - rightS;

	if(diffL > -50 && diffL < 50 && diffR > -50 && diffR < 50){
		isForward = true;
	}
	else{
		isForward = false;


	}

	//right = .0;
	//left = .0;
	ROS_INFO("reactiveControlFunction");

	ROS_INFO("leftS = %lf rightS = %lf diffL = %lf diffR = %lf",leftS,rightS, diffL, diffR);
}


//we want the boat to stay within 350-425 range finders for sensors
//Get feedback from fanboat
void reactiveControl::sensorFilter_callback(const fanboat_ll::fanboatLL::ConstPtr& f_ll)
{
	fll = *f_ll;
	lab2::angle_msg msg;
	
	ROS_INFO("reactiveControl");
	leftS = fll.a0;
	rightS = fll.a1;
	if (initLeftS == -100){
		initLeftS = leftS;
	}
	if (initRightS == -100){
		initRightS = rightS;
	}
	reactive();
	//motors_pub_.publish(boat);
}

double getAngle(){
	return 0.0;
}


int main(int argc, char** argv)
{
	
	ros::init(argc, argv, "reactiveControl");
	reactiveControl reactiveControl;
	lab2::angle_msg boat;
	ros::Rate loop_rate(12);//sets the f to 12Hz
	ros::NodeHandle nh;

	
	while(ros::ok()) {
		if(isMapping){
			ROS_INFO(" ");

		}
		else if(isForward){
			boat.angle = 0;
			boat.thrust = .35;
		}
		else if(!isForward){
			boat.angle = getAngle();
			boat.thrust = 0;
		}

		//angles_pub_.publish(boat);
		ros::spinOnce();
		loop_rate.sleep();
	}


	ros::spin();
}
