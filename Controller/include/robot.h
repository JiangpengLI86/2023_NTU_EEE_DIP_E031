#pragma once
#include <string>
#include <list>


enum command_type
{
	Motor,
	Servo
};

struct command {
	command_type type;
	float value_1 = 0.0;
	float value_2 = 0.0;
	float value_3 = 0.0;
	float value_4 = 0.0;
	float value_5 = 0.0;
	float value_6 = 0.0;
};


class Robot
{
public: // Static Class Attributes
	static float max_speed;

public:  // Instance Public Attributes
	std::string name;

public:  // Instance Public Methods
	Robot(std::string iname, std::string iaddress);
	void stop();
	void go_forward(int speed);
	void go_backward(int speed);
	void turn_left(int speed);
	void turn_right(int speed);
	void cam_turn_left();
	void cam_turn_right();
	void step();
	void _read_sensor();
	void send_int(std::string instruct);
	void send_cam(std::string instruct);
	void _disconnect();


private:  // Instance Private Attributes
	std::string _address;
	std::list<command> _actuators_to_write;  // [struct command 1, struct command 2, ...]
	std::string _sensors_to_read;  // Not decided yet.


private:  // Instance Private Methods
	void _send(command_type type, float variable_1);  // Send out information that only has one variable.
	void _send(command_type type, float variable_1, float variable_2);  // Send out information that has two variables.
	void _receive();
	void _write_actuator();
	void _connect();


};