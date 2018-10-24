#pragma once

#include "KeyboardState.h"
#include "Keyboard.h"

class InputHelper
{
public:
	static void Update();

	static bool IsKeyDown(int keyCode);
	static bool IsKeyUp(int keyCode);
	static bool IsKeyPressed(int keyCode);

private:
	static KeyboardState currentKeyboardState;
	static KeyboardState previousKeyboardState;
};