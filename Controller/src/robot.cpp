#include <WinSock2.h>
#include <WS2tcpip.h>
#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <list>
#include <cmath>
#include <dos.h>
#include "robot.h"

using namespace std;

// Initial defines, which will be redefined if necessary.
SOCKET clientSocket;
int current_speed2;
int cam_angle = 0;
float Robot::max_speed = 255.0;  


Robot::Robot(std::string iname, std::string iaddress)
{
	// Constructor
	name = iname;
	_address = iaddress;

	std::cout << "A Robot object called " << name << " with address: " << _address << " is created. \n";

	_connect();

}


void Robot::step()
{
	// Write actuator and then reset this variable
	_write_actuator();
	std::list<command> _actuators_to_write;

	// Read sensor
	//_read_sensor();

}


void Robot::_connect()
{
	// Connect to robot
	cout << "Step 1 - Setting up DLL" << endl;

	int port = 100;
	WSADATA wsaData;
	int wsaerr;
	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0)
	{
		cout << "The Winsock dll not found!" << endl;
	}
	else
	{
		cout << "The Winsock dll found!" << endl;
		cout << "The Status: " << wsaData.szSystemStatus << endl;
	}

	cout << "Step 2 - Set up Client Socket" << endl;
	clientSocket = INVALID_SOCKET;
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET)
	{
		cout << "Error At socket(): " << WSAGetLastError() << endl;

	}
	else
	{
		cout << "socket() is OK!" << endl;
	}

	cout << "Step 3 - Connect with Server Socket" << endl;

	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	InetPton(AF_INET, _T("192.168.59.246/"), &clientService.sin_addr.s_addr);
	clientService.sin_port = htons(port);
	if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR)
	{
		cout << "Client: connect() - Failed to connect." << endl;
		WSACleanup();

	}
	else
	{
		cout << "Client: connect() is OK!" << endl;
		cout << "Client: Can start sending and receiving data..." << endl;
	}

	cout << "Step 4 - Chat to the Server" << endl;
}

void Robot::_disconnect()
{
	cout << "Step 5 - Close Socket" << endl;

	WSACleanup();
}


void Robot::_send(command_type type, float variable_1)
{
	// sending information via WIFI
}

void Robot::_send(command_type type, float variable_1, float variable_2)
{
	// sending information via WIFI
}

void Robot::send_int(std::string instruct)
{
	string tell = "{\"N\":100";

	// Execute instructions
	if (instruct == "w")
	{
		tell = "{\"N\":102,\"D1\":1,\"D2\":" + to_string(current_speed2) + "}";
	}
	else if (instruct == "s")
	{
		tell = "{\"N\":102,\"D1\":2,\"D2\":" + to_string(current_speed2) + "}";
	}
	else if (instruct == "a")
	{
		tell = "{\"N\":102,\"D1\":3,\"D2\":" + to_string(current_speed2) + "}";
	}
	else if (instruct == "d")
	{
		tell = "{\"N\":102,\"D1\":4,\"D2\":" + to_string(current_speed2) + "}";
	}
	else if (instruct == "p")
	{
		tell = "{\"N\":100}";
	}


	char buffer[200];
	strcpy_s(buffer, tell.c_str());


	int byteCount = send(clientSocket, buffer, 200, 0);

	if (byteCount > 0)
	{
		cout << "Message sent: " << buffer << endl;
	}
	else
	{
		WSACleanup();
	}

	/*byteCount = recv(clientSocket, buffer, 200, 0);

	if (byteCount > 0)
	{
		cout << "Message received: " << buffer << endl;
	}
	else
	{
		WSACleanup();
	}*/
	Sleep(35);
}

void Robot::send_cam(std::string instruct)
{
	string tell = "{\"N\":106,\"D1\":";
	if (instruct == "m")
	{
		tell.append("4}");
		if (cam_angle < 8)
            {
                cam_angle += 1;
            }
            std::cout << cam_angle << std::endl;
	}
	if (instruct == "n")
	{
		tell.append("3}");
		if (cam_angle > -8)
            {
                cam_angle -= 1;
            }

            std::cout << cam_angle << std::endl;
	}
	

	char buffer[200];
	strcpy_s(buffer, tell.c_str());


	int byteCount = send(clientSocket, buffer, 200, 0);

	if (byteCount > 0)
	{
		cout << "Message sent: " << buffer << endl;
	}
	else
	{
		WSACleanup();
	}

	/*byteCount = recv(clientSocket, buffer, 200, 0);

	if (byteCount > 0)
	{
		cout << "Message received: " << buffer << endl;
	}
	else
	{
		WSACleanup();
	}*/
	Sleep(500);
}


void Robot::_receive()
{
	// receiving information via WIFI
}


void Robot::_write_actuator()
{
	// Write actuator

	// Loop through every actuators
	for (auto com_iter = _actuators_to_write.begin(); com_iter != _actuators_to_write.end(); com_iter++) {

		command_type type = com_iter->type;

		switch (type)
		{
		case Motor: {
			// Drive the motor

			float left_speed = com_iter->value_1;
			float right_speed = com_iter->value_2;
			_send(Motor, left_speed, right_speed);
			break;
		}
		case Servo: {
			// Drive the servo
		}
		}
	}
}


void Robot::_read_sensor()
{
	// Read sensor

}

void Robot::stop()
{
	std::cout << "Robot " << name << " is stationary. \n";
	current_speed2 = 0;
	send_int("p");
}

void Robot::go_forward(int speed) 	// Go forward
{
	current_speed2 = speed;
	std::cout << "Robot " << name << " is going forward. \n";
	send_int("w");
}

void Robot::go_backward(int speed) 	// Go backward
{
	current_speed2 = speed;
	std::cout << "Robot " << name << " is going backward. \n";
	send_int("s");
}

void Robot::turn_left(int speed) 	// Turn left
{
	current_speed2 = speed;
	std::cout << "Robot " << name << " is turning left. \n";
	send_int("a");
}

void Robot::turn_right(int speed) // Turn right
{
	current_speed2 = speed;
	std::cout << "Robot " << name << " is turning right. \n";
	send_int("d");
}

void Robot::cam_turn_left()
{
	//Cam turn left
	std::cout << "Camera is turning left. \n";
	send_cam("n");
}

void Robot::cam_turn_right()
{
	//Cam turn right
	std::cout << "Camera is turning right. \n";
	send_cam("m");

}