#pragma once

#include "DirectInput.h"
#include "Keyboard.h"
#include "Mouse.h"

class GameInput
{
public:
	void Initialize(HWND handle);
	Keyboard &GetKeyboard();
	Mouse &GetMouse();
	void Update();
	
	~GameInput();

private:
	Keyboard keyboard;
	Mouse mouse;
};