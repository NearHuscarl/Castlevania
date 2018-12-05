#include "InputHelper.h"
#include "Keyboard.h"
#include "Mouse.h"

KeyboardState InputHelper::currentKeyboardState = nullptr;
KeyboardState InputHelper::previousKeyboardState = nullptr;

MouseState InputHelper::currentMouseState;
MouseState InputHelper::previousMouseState;

void InputHelper::Update()
{
	previousKeyboardState = currentKeyboardState;
	currentKeyboardState = Keyboard::GetState();

	previousMouseState = currentMouseState;
	currentMouseState = Mouse::GetState();
}

bool InputHelper::IsKeyDown(int keyCode)
{
	return previousKeyboardState.IsKeyUp(keyCode) && currentKeyboardState.IsKeyDown(keyCode);
}

bool InputHelper::IsKeyUp(int keyCode)
{
	return previousKeyboardState.IsKeyDown(keyCode) && currentKeyboardState.IsKeyUp(keyCode);
}

bool InputHelper::IsKeyPressed(int keyCode)
{
	return previousKeyboardState.IsKeyDown(keyCode) && currentKeyboardState.IsKeyDown(keyCode);
}

bool InputHelper::IsMouseHold(MouseButton mouseButton)
{
	return previousMouseState.IsPressed(mouseButton) && currentMouseState.IsPressed(mouseButton);
}

bool InputHelper::IsMouseReleased(MouseButton mouseButton)
{
	return previousMouseState.IsPressed(mouseButton) && currentMouseState.IsReleased(mouseButton);
}

bool InputHelper::IsScrollingUp()
{
	return currentMouseState.scrollWheelValue > 0;
}

bool InputHelper::IsScrollingDown()
{
	return currentMouseState.scrollWheelValue < 0;
}

Vector2 InputHelper::GetMousePosition()
{
	return Vector2{ currentMouseState.x, currentMouseState.y };
}
