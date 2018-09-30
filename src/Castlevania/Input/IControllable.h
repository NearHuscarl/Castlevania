#pragma once

#include "../Utilities/Event.h"
#include "InputManager.h"
#include "KeyEventArgs.h"


EVENT_RECEIVER
class IControllable
{
protected:
	virtual void HookEvents() = 0;
	virtual void UnhookEvents() = 0;

	virtual void OnKeyStateChanged(InputManager *inputManager) {};
	virtual void OnKeyDown(InputManager *inputManager, KeyEventArgs e) {};
	virtual void OnKeyUp(InputManager *inputManager, KeyEventArgs e) {};
};