#include <iostream>  // std::cout
#include <windows.devices.wifi.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

void cam_main(std::atomic<bool>& stop_flag)
{
	VideoCapture cap;
	cap.open("http://192.168.59.246:81/stream", CAP_ANY); //Enter Camera IP Address
	if (!cap.isOpened())
	{
		std::cout << "Camera not linked.\n";
	}
	namedWindow("Robot View", WINDOW_AUTOSIZE);
	Mat frame;

	while (!stop_flag)  // Try to jump out of the loop when the main function is terminated.
	{
		bool check = cap.read(frame);
		if (!check)
		{
			std::cout << "No Image Connected.\n";
			break;
		}
		imshow("Robot View", frame);
		waitKey(1);
	}
}
