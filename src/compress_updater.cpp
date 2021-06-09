#include "ros/ros.h"
#include "std_msgs/String.h"
#include <string>
#include <sstream>
#include <iostream>

int main(int argc, char **argv)
{

  ros::init(argc, argv, "compression_updater");

  ros::NodeHandle n;

  //ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);

  ros::Rate loop_rate(1);
  int quality = 80;
  while (ros::ok())
  {
    if (quality > 80){
      quality = 10;
    }
    //std::string quality_str = "rosrun dynamic_reconfigure dynparam set /camera/compressed jpeg_quality";

    std::string quality_str = std::to_string(quality);
    system(("rosrun dynamic_reconfigure dynparam set /camera/compressed jpeg_quality" + quality_str).c_str());
    //ROS_INFO("%s", msg.data.c_str());

    //chatter_pub.publish(msg);
    quality+=10;
    ros::spinOnce();
    loop_rate.sleep();
  }


  return 0;
}
