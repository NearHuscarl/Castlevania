#include "GameInput.h"

void GameInput::Initialize(HWND handle)
{
	DirectInput::Initialize(handle);

	keyboard.Initialize();
	mouse.Initialize();
}

Keyboard &GameInput::GetKeyboard()
{
	return keyboard;
}

Mouse &GameInput::GetMouse()
{
	return mouse;
}

void GameInput::Update()
{
	keyboard.Update();
}

GameInput::~GameInput()
{
	keyboard.Release();
	mouse.Release();
}
