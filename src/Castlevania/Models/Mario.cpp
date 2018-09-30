#include "Mario.h"
#include "../Input/InputManager.h"
#include "../Utilities/Debug.h"


Mario::Mario()
{
	HookEvents();
}

void Mario::HookEvents()
{
	HOOK_EVENT(&InputManager::KeyDown, InputManager::GetInstance(), &Mario::OnKeyDown);
	HOOK_EVENT(&InputManager::KeyStateChanged, InputManager::GetInstance(), &Mario::OnKeyStateChanged);
}

void Mario::Update(DWORD dt)
{
	GameObject::Update(dt);

	// simple JUMP
	vy += MARIO_GRAVITY;
	if (y > 100) 
	{
		vy = 0; y = 100.0f;
	}

	// simple screen edge collision!!!
	if (vx > 0 && x > 280) x = 280;
	if (vx < 0 && x < 0) x = 0;
}

void Mario::Render()
{
	int ani;
	if (vx == 0)
	{
		if (nx>0) ani = MARIO_ANI_IDLE_RIGHT;
		else ani = MARIO_ANI_IDLE_LEFT;
	}
	else if (vx > 0) 
		ani = MARIO_ANI_WALKING_RIGHT; 
	else ani = MARIO_ANI_WALKING_LEFT;

	animations[ani]->Render(x, y);
}

void Mario::SetState(int state)
{
	GameObject::SetState(state);
	switch (state)
	{
		case MARIO_STATE_WALKING_RIGHT:
			vx = MARIO_WALKING_SPEED;
			nx = 1;
			break;
		case MARIO_STATE_WALKING_LEFT:
			vx = -MARIO_WALKING_SPEED;
			nx = -1;
			break;
		case MARIO_STATE_JUMP:
			vy = -MARIO_JUMP_SPEED_Y;

		case MARIO_STATE_IDLE:
			vx = 0;
			break;
	}
}

void Mario::OnKeyDown(InputManager *inputManager, KeyEventArgs e)
{
	DebugOut(L"[INFO] KeyDown: %d\n", e.KeyCode);
	switch (e.KeyCode)
	{
		case DIK_SPACE:
			SetState(MARIO_STATE_JUMP);
			break;
	}
}

void Mario::OnKeyUp(InputManager *inputManager, KeyEventArgs e)
{
	DebugOut(L"[INFO] KeyUp: %d\n", e.KeyCode);
}

void Mario::OnKeyStateChanged(InputManager *inputManager)
{
	if (inputManager->IsKeyDown(DIK_RIGHT))
	{
		SetState(MARIO_STATE_WALKING_RIGHT);
	}
	else if (inputManager->IsKeyDown(DIK_LEFT))
	{
		SetState(MARIO_STATE_WALKING_LEFT);
	}
	else
	{
		SetState(MARIO_STATE_IDLE);
	}
}

void Mario::UnhookEvents()
{
	UNHOOK_EVENT(&InputManager::KeyDown, InputManager::GetInstance(), &Mario::OnKeyDown);
	UNHOOK_EVENT(&InputManager::KeyStateChanged, InputManager::GetInstance(), &Mario::OnKeyStateChanged);
}

Mario::~Mario()
{
	UnhookEvents();
}