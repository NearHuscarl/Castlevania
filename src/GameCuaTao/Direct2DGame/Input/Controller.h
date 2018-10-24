#pragma once

#include "../Utilities/Event.h"
#include "Keyboard.h"
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

	virtual void OnKeyState(Keyboard &inputManager) {};
	virtual void OnKeyDown(Keyboard &inputManager, KeyEventArgs e) {};
	virtual void OnKeyUp(Keyboard &inputManager, KeyEventArgs e) {};
};