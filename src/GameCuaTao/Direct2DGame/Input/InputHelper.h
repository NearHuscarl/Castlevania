#pragma once

#include "Keyboard.h"
#include "KeyboardState.h"

class InputHelper
{
public:
	static void Initialize(Keyboard *keyboard);
	static void Update();

	static bool IsKeyDown(int keyCode);
	static bool IsKeyUp(int keyCode);
	static bool IsKeyPressed(int keyCode);

private:
	static Keyboard *keyboard;
	static KeyboardState currentKeyboardState;
	static KeyboardState previousKeyboardState;
};