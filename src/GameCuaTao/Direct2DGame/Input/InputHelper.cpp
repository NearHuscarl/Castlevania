#include "InputHelper.h"

Keyboard *InputHelper::keyboard = nullptr;
KeyboardState InputHelper::currentKeyboardState = nullptr;
KeyboardState InputHelper::previousKeyboardState = nullptr;

void InputHelper::Initialize(Keyboard *keyboard)
{
	InputHelper::keyboard = keyboard;
}

void InputHelper::Update()
{
	previousKeyboardState = currentKeyboardState;
	currentKeyboardState = keyboard->GetState();
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