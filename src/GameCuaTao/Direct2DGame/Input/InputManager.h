#pragma once

#include <dinput.h>
#include "KeyEventArgs.h"
#include "../Utilities/Event.h"

using Input_ = LPDIRECTINPUT8;
using InputDevice_ = LPDIRECTINPUTDEVICE8;
using DeviceInputData = DIDEVICEOBJECTDATA;

EVENT_SOURCE
class InputManager
{
public:
	static InputManager &GetInstance();

	void InitKeyboard(HWND hWnd);
	void ProcessKeyboard();

	bool IsKeyDown(int KeyCode);
	bool IsKeyUp(int KeyCode);

	EVENT void KeyStateChanged(InputManager &inputManager);
	EVENT void KeyDown(InputManager &inputManager, KeyEventArgs e);
	EVENT void KeyUp(InputManager &inputManager, KeyEventArgs e);

private:
	InputManager();

	static constexpr int KEYBOARD_BUFFER_SIZE = 1024;

	Input_ input; // The DirectInput object
	InputDevice_ inputDevice; // The keyboard device
	
	BYTE keyStates[256]; // DirectInput keyboard state buffer 
	DeviceInputData keyEvents[KEYBOARD_BUFFER_SIZE]; // Buffered keyboard data
};