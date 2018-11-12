#pragma once

#include "DirectInput.h"
#include "IController.h"
#include "KeyboardState.h"

constexpr int KEYBOARD_BUFFER_SIZE = 1024;

class Keyboard
{
public:
	Keyboard();

	void Initialize(HWND handle);
	static void Register(IController *controller);
	KeyboardState GetState();
	void Update();
	void Release();

private:
	static IController *controller;

	Input_ input; // The DirectInput object
	InputDevice_ inputDevice; // The keyboard device
	DeviceInputData keyEvents[KEYBOARD_BUFFER_SIZE]; // Buffered keyboard data

	void HandleEvents();
};