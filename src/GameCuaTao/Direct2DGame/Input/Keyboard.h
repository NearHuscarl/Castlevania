#pragma once

#include "DirectInput.h"
#include "KeyboardState.h"

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