#pragma once

#define DIRECTINPUT_VERSION 0x800

#include <dinput.h>
#include "KeyboardState.h"

using Input_ = LPDIRECTINPUT8;
using InputDevice_ = LPDIRECTINPUTDEVICE8;
using DeviceInputData = DIDEVICEOBJECTDATA;

class Keyboard
{
public:
	static void Initialize(HWND hWnd);
	static KeyboardState GetState();
	static void Release();

private:
	static constexpr int KEYBOARD_BUFFER_SIZE = 1024;
	
	static Input_ input; // The DirectInput object
	static InputDevice_ inputDevice; // The keyboard device
};