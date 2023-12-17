#include <cmath>     // ceil()
#include <iostream>  // std::cout
#include <mutex>
#include <string>    // std::string
#include <thread>    // std::thread
#include <windows.h>

#include "direct_input_wheel_read.h" // DirectInput wheel reading class
#include "robot.h"  // robot control class

// ------------------------------
// For steering wheel reading purpose
char input_command = ' ';
int current_speed1;
// ------------------------------

// Entry point.
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    SetupConsole();
    auto devices = EnumerateDevices();

    if (devices.size() == 0)
    {
        printf("No DirectInput devices found.\n");
        system("pause");
        return 0;
    }

    auto device = devices[0];

    // ------------------------------
    // Do some initial settings here, like connection, etc.
    Robot robot = Robot("robot_1");  // Create robot object
    // ------------------------------

    // ------------------------------
    // This is the main loop.
    bool steeringWheelActivated = false;  // Flag to track whether the steering wheel is activated

    bool stop_critera = false;
    bool moving = false;
    while (stop_critera == false) // Exit program if 'ESC' is hitted.
    {
        // Read the device state. This is where all buttons and axes are reported.
        DIJOYSTATE2 input;
        device->GetDeviceState(sizeof(input), &input);

        // Check if the steering wheel is activated
        if (input.lX != 32767) 
        {
            steeringWheelActivated = true;
        }
        if (GetAsyncKeyState(VK_ESCAPE)) // When ESC key is pressed, stop program
        {
            stop_critera = true;
            robot.stop();
            break;
        }
        if (input.lY < 65535 && steeringWheelActivated == true) // Throttle is pressed
        {   // Get the speed first and then send it to the robot
            moving = true;
            input_command = 'W';
            current_speed1 = ceil(((65535 - input.lY)/65535.0)*160) + 30; //current_speed1 is categorized in a range 10 to 200
            robot.go_forward(current_speed1);
        }
        else if (input.lRz < 65535 && steeringWheelActivated == true) // Brake (Reverse) is pressed
        {
            moving = true;
            input_command = 'S';
            current_speed1 = ceil(((65535 - input.lRz)/65535.0)*160) + 30;
            robot.go_backward(current_speed1);
        }
        else if (input.lX <= 30567 && steeringWheelActivated == true) // Steering wheel left
        {   
            moving = true;
            input_command = 'A';
            current_speed1 = ceil(((30567 - input.lX)/30567.0)*155) + 50;
            robot.turn_left(current_speed1);
        }
        else if (input.lX >= 34967 && steeringWheelActivated == true) // Steering wheel right
        {
            moving = true;
            input_command = 'D';
            current_speed1 = ceil(((input.lX - 34967)/30568.0)*155) + 50;
            robot.turn_right(current_speed1);
        }
        else if ((input.rgbButtons[5]) == 128) // Camera turn left
        {
            input_command = 'N';
            current_speed1 = 0;
            robot.cam_turn_left();
        }
        else if ((input.rgbButtons[4]) == 128) // Camera turn right
        {
            input_command = 'M';
            current_speed1 = 0;
            robot.cam_turn_right();
        }
        else //No command has been input
        { 
            if (moving == true){        
                moving = false;
                robot.stop();
            }
            continue;
        }    

        std::cout << input_command << " is pressed and speed = " << current_speed1 << ". \n";

        // Sleep
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    // ----------------------------

    // Conduct some ending code here
    std::cout << "Exit while \n";
    robot.disconnect();

    // Print the wheel axis--------------------
    // printf("Wheel: %10d\n", input.lX);
    // printf("Throttle: %10d\n", input.lY);
    // printf("Brake: %10d\n", input.lRz);
    // printf("Reverse Gear: %10d\n", input.rgbButtons[23]);
    // }

     
    for (auto const& device : devices)
    {
        // Release all acquired devices.
        device->Release();
    }
    
    return 0;
}
