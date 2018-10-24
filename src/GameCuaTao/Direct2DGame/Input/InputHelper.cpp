#include "InputHelper.h"

KeyboardState InputHelper::currentKeyboardState = KeyboardState(nullptr);
KeyboardState InputHelper::previousKeyboardState = KeyboardState(nullptr);

void InputHelper::Update()
{
	previousKeyboardState = currentKeyboardState;
	currentKeyboardState = Keyboard::GetState();
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