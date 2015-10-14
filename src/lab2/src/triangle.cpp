#include <ros/ros.h>
#include <lab2/angle_msg.h>
#include <fanboat_ll/fanboatLL.h>
#include <math.h>

int i = 0;
bool isTurning = true;
double totalDistance = 1;
double targetAngle = 0, actualAngle = 0, diff = 0;

class triangle
{
public:
  triangle();
  ros::Publisher angle_tri_pub_;

//private variables that can be accessed in callback
private:
  void fanboatLL_callback(const fanboat_ll::fanboatLL::ConstPtr& fll);
  ros::NodeHandle nh_;
  ros::Subscriber fll_sub_;
};

//setting up the button variables
triangle::triangle()
{
  fll_sub_ =  nh_.subscribe<fanboat_ll::fanboatLL>("fll_sync", 1, &triangle::fanboatLL_callback, this);
  angle_tri_pub_ = nh_.advertise<lab2::angle_msg>("angle_tri", 1);
}


void triangle::fanboatLL_callback(const fanboat_ll::fanboatLL::ConstPtr& fll)
{
	actualAngle = fll->yaw;
}



int main(int argc, char** argv)
{
    ros::init(argc, argv, "triangle");
    triangle triangle;

    ros::Rate loop_rate(12);//sets the f to 12Hz
    ros::NodeHandle nh;

    i = 0;
    double pubs = 12;

	targetAngle = actualAngle + 120;
	targetAngle = (targetAngle > 180) ? targetAngle - 360 : targetAngle; //Make sure this value stays within [-180,180]

    while(ros::ok()) {
    	double angle, thrust;
    	if(isTurning) {
    		if(fabs(targetAngle - actualAngle) < 15.0) {
    			isTurning = false;
    			targetAngle += 120;
    			targetAngle = (targetAngle > 180) ? targetAngle - 360 : targetAngle; //Make sure this value stays within [-180,180]
    		}
    		ROS_INFO("Turning - Target: %f, Actual: %f", targetAngle, actualAngle);
    		angle = targetAngle;
    		thrust = 0.2;
    	} else {
    		ROS_INFO("Straight");
			if(i < pubs) {
				angle = targetAngle;
				thrust = 0.35;
				i++;
			} else {
				i = 0; //Reset i
				isTurning = true;
			}
    	}

    lab2::angle_msg msg;
    msg.thrust = thrust;
    msg.angle = angle;
    triangle.angle_tri_pub_.publish(msg);

    ros::spinOnce();
    loop_rate.sleep();
    }
    ros::spin();
}
