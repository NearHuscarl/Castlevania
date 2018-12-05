#include "MouseState.h"

MouseState::MouseState(DIMOUSESTATE state)
{
	this->state = state;
}

MouseState::MouseState()
{
	this->state = DIMOUSESTATE{};
}

bool MouseState::IsPressed(MouseButton mouseButton)
{
	{
		switch (mouseButton)
		{
			case MouseButton::Left:
				return (state.rgbButtons[0] & 0x80);

			case MouseButton::Right:
				return (state.rgbButtons[1] & 0x80);

			case MouseButton::Middle:
				return (state.rgbButtons[2] & 0x80);

			default:
				return false;
		}
	}
}

bool MouseState::IsReleased(MouseButton mouseButton)
{
	{
		switch (mouseButton)
		{
			case MouseButton::Left:
				return !(state.rgbButtons[0] & 0x80);

			case MouseButton::Right:
				return !(state.rgbButtons[1] & 0x80);

			case MouseButton::Middle:
				return !(state.rgbButtons[2] & 0x80);

			default:
				return false;
		}
	}
}
