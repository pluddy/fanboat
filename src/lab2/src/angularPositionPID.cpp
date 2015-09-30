#include <ros/ros.h>
#include <lab2/angle_msg.h>
#include <fanboat_ll/fanboatMotors.h>
#include <fanboat_ll/fanboatLL.h>
#include <math.h>

class angularPositionPID
{
public:
	angularPositionPID();

	//Private functions/variables
private:
	void angle_callback(const lab2::angle_msg::ConstPtr& ang);
	void fanboatLL_callback(const fanboat_ll::fanboatLL::ConstPtr& ang);

	ros::NodeHandle nh_;

	ros::Publisher motors_pub_;
	ros::Subscriber angle_sub_;
	ros::Subscriber fanboatLL_sub_;
};

angularPositionPID::angularPositionPID()
{
	//Subscribe to arbitated angle messages
	fanboatLL_sub_ =  nh_.subscribe<fanboat_ll::fanboatLL>("fanboatLL", 1, &angularPositionPID::fanboatLL_callback, this);

	//Subscribe to topics to arbitrate between
	angle_sub_ = nh_.subscribe<lab2::angle_msg>("angle_arb", 1, &angularPositionPID::angle_callback, this);

	//Publish to motors topic
	motors_pub_ = nh_.advertise<fanboat_ll::fanboatMotors>("motors", 1);

}

//Variables
lab2::angle_msg ang;
fanboat_ll::fanboatLL fll;

//Get driving info and publish to fanboatLL
void angularPositionPID::angle_callback(const lab2::angle_msg::ConstPtr& am)
{
	fanboat_ll::fanboatMotors boat;

	//TODO: Call a function to do PID stuff here

	motors_pub_.publish(boat);
}

//Get feedback from fanboat
void angularPositionPID::fanboatLL_callback(const fanboat_ll::fanboatLL::ConstPtr& f_ll)
{
	fll = *f_ll;
}

int main(int argc, char** argv)
{

	ros::init(argc, argv, "angularPositionPID");
	angularPositionPID angularPositionPID;

	ros::spin();
}
