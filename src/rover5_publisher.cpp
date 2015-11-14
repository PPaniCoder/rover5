#include "ros/ros.h"
#include "rover5/moveRover5.h"

int main(int argc, char** argv) {

	ros::init(argc, argv, "rover5_publisher");
	ros::NodeHandle nh;

	ros::Publisher publisher = nh.advertise<rover5::moveRover5>("rover5_move_msg", 10);

//	ros::Rate loop_rate(1);

	while(ros::ok()) {
		rover5::moveRover5 msg;
		int input;
		input = getchar();
		
		switch (input) {
			case 'i':
			case 'j':
			case 'k':
			case 'l':
			case ',':
			case '.':
			case 'q':
				msg.direction = input;
				ROS_INFO("send msg = %c", input);
				publisher.publish(msg);
				break;
		}

//		loop_rate.sleep();	
	}
	return 0;
}
