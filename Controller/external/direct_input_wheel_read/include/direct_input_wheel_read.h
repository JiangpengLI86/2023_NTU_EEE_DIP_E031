// main.h

#ifndef MAIN_H
#define MAIN_H

#include <vector>
#include <dinput.h>

using Devices = std::vector<LPDIRECTINPUTDEVICE8>;

// Used to pass the necessary parameters to the diEnumDevicesCallback function.
struct EnumInfo
{
    Devices* devices{ nullptr };
    LPDIRECTINPUT8 directInput{ nullptr };
};

void SetupConsole();

BOOL CALLBACK EnumDevicesCallback(const DIDEVICEINSTANCE*, VOID*);

Devices EnumerateDevices();

#endif // MAIN_H