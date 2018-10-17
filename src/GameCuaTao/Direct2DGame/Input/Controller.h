#pragma once

#include "../Utilities/Event.h"
#include "InputManager.h"
#include "KeyEventArgs.h"

EVENT_RECEIVER
class Controller
{
public:
	Controller();
	virtual ~Controller();

protected:
	virtual void HookEvents();
	virtual void UnhookEvents();

	virtual void OnKeyState(InputManager &inputManager) {};
	virtual void OnKeyDown(InputManager &inputManager, KeyEventArgs e) {};
	virtual void OnKeyUp(InputManager &inputManager, KeyEventArgs e) {};
};