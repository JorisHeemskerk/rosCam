#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <ros/ros.h>
#include <sensor_msgs/image_encodings.h>

int main(int argc, char** argv)
{
	ros::init(argc, argv, "camera_pub");
	ros::NodeHandle cameraHandler;

	//init video capture.
	cv::VideoCapture videoCap;

	const int deviceID = 0;       // 0 = open default camera
    	int apiID = cv::CAP_ANY;      // 0 = autodetect default API
    	// open selected camera using selected API
    	videoCap.open(deviceID, apiID);
    	// check if videocapture succeeded
    	if (!videoCap.isOpened())
	{
        	ROS_ERROR_STREAM("ERROR! Unable to open camera");
       		ros::shutdown();
	}
	videoCap.set(CV_CAP_PROP_FRAME_WIDTH,1280);
	videoCap.set(CV_CAP_PROP_FRAME_HEIGHT,720);
	image_transport::ImageTransport it(cameraHandler);

    	// Publish to the /camera topic
    	image_transport::Publisher pub_frame = it.advertise("camera", 1);

	cv::Mat frame;//Mat is the image class defined in OpenCV
	sensor_msgs::ImagePtr msg;
	const int frameRate = 24;//The camera framerate (hz)
	ros::Rate loopRate(frameRate);

   	while (cameraHandler.ok()) //loop for camera frame publication
	{
		videoCap >> frame;
		if (frame.empty())
		{
			ROS_ERROR_STREAM("Frame is empty. shutdown");
			ros::shutdown();
		}
		msg = cv_bridge::CvImage(std_msgs::Header(), "rgb8", frame).toImageMsg();
      		pub_frame.publish(msg);
		ros::spinOnce();
		loopRate.sleep();//wait to next frame capture. Set by variable frameRate.
	}
	// Ending of capture of camera. Camera shutdown.
    	videoCap.release();
}



