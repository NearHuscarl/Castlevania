#pragma once

#include <dinput.h>
#include "KeyEventArgs.h"
#include "../Utilities/Event.h"

typedef LPDIRECTINPUT8 GInputPtr;
typedef LPDIRECTINPUTDEVICE8 GInputDevicePtr;
typedef DIDEVICEOBJECTDATA GDeviceInputData;

EVENT_SOURCE
class InputManager
{
public:
	static InputManager *GetInstance();

	void InitKeyboard(HWND hWnd);

	int IsKeyDown(int KeyCode);
	void ProcessKeyboard();

	EVENT void KeyStateChanged(InputManager *inputManager);
	EVENT void KeyDown(InputManager *inputManager, KeyEventArgs e);
	EVENT void KeyUp(InputManager *inputManager, KeyEventArgs e);

private:
	InputManager();
	static InputManager *instance;

	static constexpr int KEYBOARD_BUFFER_SIZE = 1024;

	GInputPtr input; // The DirectInput object
	GInputDevicePtr inputDevice; // The keyboard device
	
	BYTE keyStates[256]; // DirectInput keyboard state buffer 
	GDeviceInputData keyEvents[KEYBOARD_BUFFER_SIZE]; // Buffered keyboard data
};