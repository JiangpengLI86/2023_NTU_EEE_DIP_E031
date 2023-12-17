#pragma once
#include <string>
#include <list>


class Robot
{
public:  // Instance Public Attributes
	std::string name;

public:  // Instance Public Methods
	Robot(std::string iname);
	void stop();
	void go_forward(int speed);
	void go_backward(int speed);
	void turn_left(int speed);
	void turn_right(int speed);
	void cam_turn_left();
	void cam_turn_right();
	void disconnect();

private:  // Instance Private Methods
	void _connect();
	void send_int(std::string instruct);
	void send_cam(std::string instruct);

};