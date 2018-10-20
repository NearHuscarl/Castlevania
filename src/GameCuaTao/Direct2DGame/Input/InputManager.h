#pragma once

#include <dinput.h>
#include "KeyEventArgs.h"
#include "../Utilities/Event.h"

typedef LPDIRECTINPUT8 Input_;
typedef LPDIRECTINPUTDEVICE8 InputDevice_;
typedef DIDEVICEOBJECTDATA DeviceInputData_;

EVENT_SOURCE
class InputManager
{
public:
	static InputManager &GetInstance();

	void InitKeyboard(HWND hWnd);

	bool IsKeyDown(int KeyCode);
	bool IsKeyUp(int KeyCode);
	void ProcessKeyboard();

	EVENT void KeyStateChanged(InputManager &inputManager);
	EVENT void KeyDown(InputManager &inputManager, KeyEventArgs e);
	EVENT void KeyUp(InputManager &inputManager, KeyEventArgs e);

private:
	InputManager();

	static constexpr int KEYBOARD_BUFFER_SIZE = 1024;

	Input_ input; // The DirectInput object
	InputDevice_ inputDevice; // The keyboard device
	
	BYTE keyStates[256]; // DirectInput keyboard state buffer 
	DeviceInputData_ keyEvents[KEYBOARD_BUFFER_SIZE]; // Buffered keyboard data
};