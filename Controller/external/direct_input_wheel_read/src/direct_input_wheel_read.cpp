
#include <conio.h>
#include <windows.h>
#include <cstdio>

#include "direct_input_wheel_read.h"

// Define DirectInput Version
#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif


using namespace std;

// Sets up a console window to send output to.
void SetupConsole()
{
    AllocConsole();

    FILE* stream;
    freopen_s(&stream, "CONIN$", "r", stdin);
    freopen_s(&stream, "CONOUT$", "w", stderr);
    freopen_s(&stream, "CONOUT$", "w", stdout);

    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.bVisible = FALSE;
    cursorInfo.dwSize = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// Called by the direct input system when it finds a devices.
BOOL CALLBACK EnumDevicesCallback(const DIDEVICEINSTANCE* deviceInstance, VOID* pvRef)
{
    LPDIRECTINPUTDEVICE8 diDevice;
    auto data = static_cast<EnumInfo*>(pvRef);

    // Create an interface to the device.
    if (DI_OK != data->directInput->CreateDevice(deviceInstance->guidInstance, &diDevice, nullptr))
    {
        return DIENUM_CONTINUE;
    }

    // Setup the device and aquire it.
    if (DI_OK == diDevice->SetCooperativeLevel(GetConsoleWindow(), DISCL_BACKGROUND | DISCL_EXCLUSIVE))
    {
        if (DI_OK == diDevice->SetDataFormat(&c_dfDIJoystick2))
        {
            diDevice->Acquire();
            data->devices->push_back(diDevice);
            return DIENUM_CONTINUE;
        }
    }

    // If we get here we have no need for the direct input device.
    diDevice->Release();

    return DIENUM_CONTINUE;
}

// Enumerate all DirectInput devices.
Devices EnumerateDevices()
{
    Devices devices;
    EnumInfo info;
    info.devices = &devices;

    // Create the DirectInput interface.
    HRESULT result = DirectInput8Create(GetModuleHandle(nullptr),
        DIRECTINPUT_VERSION,
        IID_IDirectInput8,
        reinterpret_cast<VOID**>(&info.directInput),
        nullptr);

    if (result != DI_OK)
    {
        // Error, return what we have.
        return devices;
    }

    // Enumerate the devices.
    info.directInput->EnumDevices(DI8DEVCLASS_GAMECTRL,
        (LPDIENUMDEVICESCALLBACK)&EnumDevicesCallback,
        &info,
        DIEDFL_ATTACHEDONLY);

    // Release the DirectInput interface.
    info.directInput->Release();

    return devices;
}