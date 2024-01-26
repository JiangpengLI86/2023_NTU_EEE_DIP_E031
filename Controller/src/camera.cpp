#include <iostream> // std::cout
#include "json.hpp"
#include <fstream>
#include <windows.devices.wifi.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

void cam_main(std::atomic<bool> &stop_flag)
{
	VideoCapture cap;
	// Read the ip address of the camera from the json file at ../configuration.json with key "cam_ip"

	// Read the IP address of the camera from the JSON file
	std::ifstream config_file("../configuration.json");
	nlohmann::json config;
	config_file >> config;
	std::string cam_ip = config["cam_ip"]; 

	cap.open("http://" + cam_ip + ":81/stream", CAP_ANY); // Use the IP address from

	if (!cap.isOpened())
	{
		std::cout << "Camera not linked.\n";
	}
	namedWindow("Robot View", WINDOW_AUTOSIZE);
	Mat frame;

	while (!stop_flag) // Try to jump out of the loop when the main function is terminated.
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
