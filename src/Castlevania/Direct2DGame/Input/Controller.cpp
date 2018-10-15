#include "Controller.h"

Controller::Controller()
{
	HookEvents();
}

void Controller::HookEvents()
{
	HOOK_EVENT(&InputManager::KeyDown, InputManager::GetInstance(), &Controller::OnKeyDown);
	HOOK_EVENT(&InputManager::KeyUp, InputManager::GetInstance(), &Controller::OnKeyUp);
	HOOK_EVENT(&InputManager::KeyStateChanged, InputManager::GetInstance(), &Controller::OnKeyState);
}

void Controller::UnhookEvents()
{
	UNHOOK_EVENT(&InputManager::KeyDown, InputManager::GetInstance(), &Controller::OnKeyDown);
	UNHOOK_EVENT(&InputManager::KeyUp, InputManager::GetInstance(), &Controller::OnKeyUp);
	UNHOOK_EVENT(&InputManager::KeyStateChanged, InputManager::GetInstance(), &Controller::OnKeyState);
}

Controller::~Controller()
{
	UnhookEvents();
}