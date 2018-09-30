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

	// TODO: try pure virtual method
	EVENT void KeyStateChanged(InputManager *inputManager);
	EVENT void KeyDown(InputManager *inputManager, KeyEventArgs e);
	EVENT void KeyUp(InputManager *inputManager, KeyEventArgs e);

private:
	static constexpr int KEYBOARD_BUFFER_SIZE = 1024;

	static InputManager *instance;

	HWND hWnd;				// Window handle

	GInputPtr       di;		// The DirectInput object
	GInputDevicePtr didv;	// The keyboard device
	
	BYTE  keyStates[256];	// DirectInput keyboard state buffer 

	GDeviceInputData keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data
};