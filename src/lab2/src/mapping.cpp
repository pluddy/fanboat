#include <ros/ros.h>
#include <lab2/angle_msg.h>
#include <sensor_msgs/Joy.h>
#include <fanboat_ll/fanboatMotors.h>
#include <fanboat_ll/fanboatLL.h>
#include <math.h>

class mapping
{
public:
	mapping();
	ros::Publisher angles_pub_;

	//Private functions/variables
private:
	//void angle_callback(const lab2::angle_msg::ConstPtr& ang);
	void joy_callback(const sensor_msgs::Joy::ConstPtr& joy);

	void sensorFilter_callback(const fanboat_ll::fanboatLL::ConstPtr& ang);
	ros::NodeHandle nh_;
	int x_button, start_button, back_button;
	ros::Subscriber joy_sub_;

	ros::Subscriber sensors_sub_;

};

double pValue;
double dValue;
double rightScale;
double leftScale;
mapping::mapping(): x_button(2), start_button(7), back_button(6) //reset the diff
{
	//Subscribe to arbitated angle messages
	sensors_sub_ = nh_.subscribe<fanboat_ll::fanboatLL>("sensors", 1, &mapping::sensorFilter_callback, this);

	joy_sub_ =  nh_.subscribe<sensor_msgs::Joy>("joy", 1, &mapping::joy_callback, this);

	//Publish to angles topic
	angles_pub_ = nh_.advertise<lab2::angle_msg>("angle_map", 1);

}

//Variables
double rangeAllowance = 30;
fanboat_ll::fanboatLL fll;
double initLeftS = -100;
double initRightS = -100;
double init = 300;
double leftS, rightS, rightMotor, leftMotor, angle, thrust, diffL, diffR;
bool isForward = true;
int state = 0;
double lastYaw = 0;
double yawClose = -1000;
double yawFar = 1000;
double sensorFar = 1000;
double sensorClose = -1000;
double totalTurn = 0;
bool reactiveMapping = true;

//pulled from the arduino library.
double map(double x, double in_min, double in_max, double out_min, double out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

bool rightInRange(){
	if(diffR > -rangeAllowance && diffR < rangeAllowance){
		return true;
	}
	return false;
}

bool leftInRange(){
	if(diffL > -rangeAllowance && diffL < rangeAllowance){
		return true;
	}
	return false;
}

void doMapping(){
	diffL = initLeftS - leftS;
	diffR = initRightS - rightS;
	double currentA = fll.yaw;
	//Keep turning slowly
	thrust = 0.2;
	angle = currentA - 25;

	//Keep track of how far we've turned
	if (fabs(currentA) > fabs(lastYaw)){
		totalTurn += (fabs(currentA) - fabs(lastYaw));
	}
	else if(fabs(lastYaw) > fabs(currentA)){
		totalTurn += (fabs(lastYaw) - fabs(currentA));
	}
	lastYaw = currentA;
	ROS_INFO("leftS: %f, rightS: %f, sensorClose: %f, yawClose: %f", leftS, rightS, sensorClose, yawClose);
	//Check if there is a closer object now
	if(leftS > sensorClose) {
		sensorClose = leftS;
		yawClose = currentA;
		ROS_INFO("yawClose: %f", yawClose);
	}
	if(rightS > sensorClose) {
		sensorClose = rightS;
		yawClose = currentA;
		ROS_INFO("yawClose: %f", yawClose);
	}
	if(leftS < sensorFar) {
		sensorFar = leftS;
		yawFar = currentA;
	}
	if(rightS < sensorFar) {
		sensorFar = rightS;
		yawFar = currentA;
	}
	//Return to following
	if(fabs(totalTurn) > 360) {
		if(reactiveMapping){
			state = 1;
		} else {
			state = 2;
		}
	}

	ROS_INFO("Total turn: %f", totalTurn);
}

void turn(double angle)
{
	thrust = 0.2;
	ROS_INFO("yaw: %f, target: %f", fll.yaw, angle);
	if(fabs(fll.yaw - angle) < 10)
	{
		state = 3;
	}
}

void reactive()
{
	diffL = initLeftS - leftS;
	diffR = initRightS - rightS;
	double currentA = fll.yaw;
	thrust = 0.2;
	//lost
	if(leftS < 150 && rightS < 150) {
		//Start mapping for a new object - we're lost!!!
		//yawClose = -1000;
		//yawFar = 1000;
		state = 0;
		lastYaw = currentA;
		totalTurn = 0;

		//Start turning
		angle = currentA - 20;
		thrust = 0.2;
	}
	//both in range go straight
	else if(rightInRange() && leftInRange()){
		thrust = .2;
		angle = currentA;
		ROS_INFO("Content!");

	}
	//when both below -50 slow down
	else if(diffR <= 0 && diffL <= 0){
		thrust = 0.2;
		angle = currentA;
		ROS_INFO("Too close!!");

	}
	//when dif r > 50 and l is in range l slow down
	else if(leftInRange() && diffR >= rangeAllowance){
		angle = currentA - 25;
		ROS_INFO("Right too far!");

	}
	//when dif l > 50 and r is in range r slow down
	else if(rightInRange() && diffL >= rangeAllowance){
		angle = currentA + 25;
		ROS_INFO("Left too far!");

	}
	//when diff l < -50 and r is in range l slow down
	else if(rightInRange() && diffL <= -rangeAllowance){
		angle = currentA - 25;
		ROS_INFO("Left too close!");

	}
	//when diff r < -50 and l is in range r slow down
	else if(leftInRange() && diffR <= -rangeAllowance){
		angle = currentA + 25;
		ROS_INFO("Right too close!");

	}
	else if(diffL <=-rangeAllowance && diffR >= rangeAllowance){
		angle = currentA - 40;
		ROS_INFO("Craziness 1!");

	}
	else if(diffL >= rangeAllowance && diffR <= -rangeAllowance){
		angle = currentA + 40;
		ROS_INFO("Craziness 2!");

	}
	//when both above 50 speed up
	else if(diffR >= rangeAllowance && diffL >= rangeAllowance){
		angle = currentA;
		thrust = .45;
		ROS_INFO("Straight");
	}
	else{
		ROS_INFO("NO STATE HIT");
		ROS_INFO("NO STATE HIT");
		ROS_INFO("NO STATE HIT");
		ROS_INFO("NO STATE HIT");
		ROS_INFO("NO STATE HIT");
	}

	if(thrust < .2) thrust = .2;
	if(thrust > .5) thrust = .5;

	ROS_INFO("dL = %.0lf dR = %.0lf ang = %.0lf thrust = %.2lf lS = %.0lf lR = %.0lf", diffL, diffR, angle,thrust,leftS, rightS);
	//ROS_INFO("leftS = %f, rightS = %f", leftS, rightS);
}


void mapping::joy_callback(const sensor_msgs::Joy::ConstPtr& joy){
	if(joy->buttons[back_button]) {
		reactiveMapping = false;
	}
	if(joy->buttons[start_button]) {
		reactiveMapping = true;
	}
	if(joy->buttons[x_button]) {
		yawClose = -1000;
		yawFar = -1000;
		sensorClose = -1000;
		sensorFar = 2000;
		state = 0;
		lastYaw = fll.yaw;
		totalTurn = 0;
	}
}



//we want the boat to stay within 350-425 range finders for sensors
//Get feedback from fanboat
void mapping::sensorFilter_callback(const fanboat_ll::fanboatLL::ConstPtr& f_ll)
{
	fll = *f_ll;
	lab2::angle_msg boat;

	//ROS_INFO("mapping");
	leftS = fll.a0;
	rightS = fll.a1;
	if (initLeftS == -100){
		initLeftS = 300;
	}
	if (initRightS == -100){
		initRightS = 300;
	}

	if(state == 0){
		doMapping();
		ROS_INFO("MAPPING");
	} else if (state == 1){
		turn(yawClose);
		ROS_INFO("TURN CLOSE");
	} else if (state == 2){
		turn(yawFar);
		ROS_INFO("TURN FAR");
	} else if (state == 3){
		reactive();
		ROS_INFO("GO TO THERE");
	}

	boat.angle = angle;
	boat.thrust = thrust;
	angles_pub_.publish(boat);
}

int main(int argc, char** argv)
{

	ros::init(argc, argv, "mapping");
	mapping mapping;


	ros::spin();
}
