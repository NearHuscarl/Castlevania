#include "Mario.h"
#include "../Utilities/FileLogger.h"

constexpr float MARIO_WALKING_SPEED = 0.05f;
constexpr float MARIO_JUMP_SPEED_X = 1.0f;
constexpr float MARIO_JUMP_SPEED_Y = 0.7f;
constexpr float MARIO_GRAVITY = 0.05f;

void Mario::LoadContent(ContentManager &content)
{
	InitAnimation({ MARIO_IDLE_LEFT, MARIO_IDLE_RIGHT, MARIO_WALK_LEFT, MARIO_WALK_RIGHT });
	SetPosition(0.0f, 100.0f);
}

void Mario::Update(unsigned long deltaTime)
{
	GameObject::Update(deltaTime);

	// simple fall down
	vy += MARIO_GRAVITY;
	if (y > 100) 
	{
		vy = 0;
		y = 100.0f;
	}

	// simple screen edge collision!!!
	if (vx > 0 && x > 290)
		x = 290;
	if (vx < 0 && x < 0)
		x = 0;

	animations[GetAnimationState()]->Update();
}

void Mario::Draw(ID3DXSprite *spriteHandler)
{
	animations[GetAnimationState()]->Draw(spriteHandler, x, y);
}

void Mario::SetState(int state)
{
	GameObject::SetState(state);
	switch (state)
	{
		case MARIO_STATE_WALK_RIGHT:
			vx = MARIO_WALKING_SPEED;
			nx = 1;
			break;
		case MARIO_STATE_WALK_LEFT:
			vx = -MARIO_WALKING_SPEED;
			nx = -1;
			break;
		case MARIO_STATE_JUMP:
			if (y == 100)
				vy = -MARIO_JUMP_SPEED_Y;
		case MARIO_STATE_IDLE:
			vx = 0;
			break;
	}
}

std::string Mario::GetAnimationState()
{
	if (vx == 0)
	{
		if (nx > 0)
			return MARIO_IDLE_RIGHT;
		else
			return MARIO_IDLE_LEFT;
	}
	else if (vx > 0)
	{
		return MARIO_WALK_RIGHT;
	}
	return MARIO_WALK_LEFT;
}

#pragma region INPUT HANDLER

void Mario::OnKeyDown(InputManager *inputManager, KeyEventArgs e)
{
	FileLogger::GetInstance()->Info("KeyDown: " + std::to_string(e.KeyCode));
	switch (e.KeyCode)
	{
		case DIK_SPACE:
			SetState(MARIO_STATE_JUMP);
			break;
	}
}

void Mario::OnKeyUp(InputManager *inputManager, KeyEventArgs e)
{
	FileLogger::GetInstance()->Info("KeyUp: " + std::to_string(e.KeyCode));
}

void Mario::OnKeyState(InputManager *inputManager)
{
	if (inputManager->IsKeyDown(DIK_RIGHT))
	{
		SetState(MARIO_STATE_WALK_RIGHT);
	}
	else if (inputManager->IsKeyDown(DIK_LEFT))
	{
		SetState(MARIO_STATE_WALK_LEFT);
	}
	else
	{
		SetState(MARIO_STATE_IDLE);
	}
}

#pragma endregion