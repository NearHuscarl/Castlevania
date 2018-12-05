#pragma once

#include "DirectInput.h"
#include "IController.h"
#include "KeyboardState.h"

constexpr auto KEYBOARD_BUFFER_SIZE = 1024;

class Keyboard
{
public:
	Keyboard();

	void Initialize();
	static void Register(IController *controller);
	static KeyboardState GetState();
	void Update();
	void Release();

private:
	static IController *controller;
	static InputDevice_ inputDevice; // The keyboard device

	void HandleEvents();
};