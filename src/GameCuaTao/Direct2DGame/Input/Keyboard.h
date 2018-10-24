#pragma once

#include <dinput.h>
#include "KeyEventArgs.h"
#include "../Utilities/Event.h"

using Input_ = LPDIRECTINPUT8;
using InputDevice_ = LPDIRECTINPUTDEVICE8;
using DeviceInputData = DIDEVICEOBJECTDATA;

EVENT_SOURCE
class Keyboard
{
public:
	static Keyboard &GetInstance();

	void Initialize(HWND hWnd);
	void ProcessKeyboard();

	bool IsKeyDown(int KeyCode);
	bool IsKeyUp(int KeyCode);

	EVENT void KeyStateChanged(Keyboard &inputManager);
	EVENT void KeyDown(Keyboard &inputManager, KeyEventArgs e);
	EVENT void KeyUp(Keyboard &inputManager, KeyEventArgs e);
	
	~Keyboard();

private:
	Keyboard();

	static constexpr int KEYBOARD_BUFFER_SIZE = 1024;

	Input_ input; // The DirectInput object
	InputDevice_ inputDevice; // The keyboard device
	
	BYTE keyStates[256]; // DirectInput keyboard state buffer 
	DeviceInputData keyEvents[KEYBOARD_BUFFER_SIZE]; // Buffered keyboard data
};