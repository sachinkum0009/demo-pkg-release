#include "ros/ros.h"
#include "master_ros/demo_srv.h"
#include <iostream>
#include <sstream>
using namespace std;

int main(int argc, char **argv)
{
    ros::init(argc, argv, "demo_service_client");
    ros::NodeHandle n;
    ros::Rate loop_rate(10);
    ros::ServiceClient client = n.serviceClient<master_ros::demo_srv>("demo_service");
    while(ros::ok())
    {
	master_ros::demo_srv srv;
	std::stringstream ss;
	ss << "Sending from here";
	srv.request.in = ss.str();
	if (client.call(srv))
	{
	    ROS_INFO("From Client [%s], Server says [%s]", srv.request.in.c_str(), srv.response.out.c_str());
	}
	else
	{
	    ROS_ERROR("Failed to call service");
	    return 1;
	}

	ros::spinOnce();
	loop_rate.sleep();
	}

    return 0;
}
