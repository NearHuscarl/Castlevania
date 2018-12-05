#pragma once

#define DIRECTINPUT_VERSION 0x800
#include <dinput.h>

using Input_ = LPDIRECTINPUT8;
using InputDevice_ = LPDIRECTINPUTDEVICE8;
using DeviceInputData = DIDEVICEOBJECTDATA;

class DirectInput
{
public:
	static void Initialize(HWND handle);
	static Input_ GetInput();
	static HWND GetHandle();

private:
	static Input_ input; // The DirectInput object
	static HWND handle;
};