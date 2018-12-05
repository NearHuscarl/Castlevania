#pragma once

#include "KeyboardState.h"
#include "MouseState.h"

class InputHelper
{
public:
	static void Update();

	static bool IsKeyDown(int keyCode);
	static bool IsKeyUp(int keyCode);
	static bool IsKeyPressed(int keyCode);
	static bool IsMouseHold(MouseButton mouseButton);
	static bool IsMouseReleased(MouseButton mouseButton);
	static bool IsScrollingUp();
	static bool IsScrollingDown();
	static Vector2 GetMousePosition();

private:
	static KeyboardState currentKeyboardState;
	static KeyboardState previousKeyboardState;
	static MouseState currentMouseState;
	static MouseState previousMouseState;
};