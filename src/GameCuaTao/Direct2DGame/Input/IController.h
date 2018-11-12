#pragma once

#include "KeyboardState.h"

class IController
{
public:
	virtual void OnKeyStateChanged(KeyboardState &keyboardState) = 0;
	virtual void OnKeyDown(int KeyCode) = 0;
	virtual void OnKeyUp(int KeyCode) = 0;
};