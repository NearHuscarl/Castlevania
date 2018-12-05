#pragma once

#include "DirectInput.h"
#include "../Base/Vector2.h"

enum class MouseButton
{
	Left,
	Right,
	Middle,
};

struct MouseState
{
	MouseState(DIMOUSESTATE state);
	MouseState();

	bool IsPressed(MouseButton mouseButton);
	bool IsReleased(MouseButton mouseButton);

	float x;
	float y;
	int scrollWheelValue;

private:
	DIMOUSESTATE state;
};