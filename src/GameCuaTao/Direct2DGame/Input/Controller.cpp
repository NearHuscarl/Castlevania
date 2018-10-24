#include "Controller.h"

Controller::Controller()
{
	HookEvents();
}

void Controller::HookEvents()
{
	HOOK_EVENT(&Keyboard::KeyDown, &Keyboard::GetInstance(), &Controller::OnKeyDown);
	HOOK_EVENT(&Keyboard::KeyUp, &Keyboard::GetInstance(), &Controller::OnKeyUp);
	HOOK_EVENT(&Keyboard::KeyStateChanged, &Keyboard::GetInstance(), &Controller::OnKeyState);
}

void Controller::UnhookEvents()
{
	UNHOOK_EVENT(&Keyboard::KeyDown, &Keyboard::GetInstance(), &Controller::OnKeyDown);
	UNHOOK_EVENT(&Keyboard::KeyUp, &Keyboard::GetInstance(), &Controller::OnKeyUp);
	UNHOOK_EVENT(&Keyboard::KeyStateChanged, &Keyboard::GetInstance(), &Controller::OnKeyState);
}

Controller::~Controller()
{
	UnhookEvents();
}