#pragma once

#include "DirectInput.h"
#include "MouseState.h"

constexpr auto MOUSE_BUFFER_SIZE = 16;

class Mouse
{
public:
	void Initialize();
	static MouseState GetState();
	void Release();

private:
	static InputDevice_ inputDevice;
};