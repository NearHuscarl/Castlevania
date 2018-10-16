#include "Direct2DGame/Utilities/FileLogger.h"
#include "Mario.h"
#include "MarioSettings.h"

constexpr float MARIO_WALKING_SPEED = 0.05f;
constexpr float MARIO_JUMP_SPEED_X = 1.0f;
constexpr float MARIO_JUMP_SPEED_Y = 0.7f;
constexpr float MARIO_GRAVITY = 0.05f;

void Mario::LoadContent(ContentManager &content)
{
	animations = content.Load<AnimationDict>("MarioAnimationDef.xml");

	SetPosition(0.0f, 100.0f);
}

void Mario::Update(unsigned long deltaTime)
{
	GameObject::Update(deltaTime);

	// simple fall down
	velocity.y += MARIO_GRAVITY;
	if (position.y > 100) 
	{
		velocity.y = 0;
		position.y = 100.0f;
	}

	// simple screen edge collision!!!
	if (velocity.x > 0 && position.x > 290)
		position.x = 290;
	if (velocity.x < 0 && position.x < 0)
		position.x = 0;

	(*animations)[GetAnimationState()].Update();
}

void Mario::Draw(ISpriteHandler_ spriteHandler)
{
	(*animations)[GetAnimationState()].Draw(spriteHandler, position);
}

void Mario::SetState(int state)
{
	GameObject::SetState(state);
	switch (state)
	{
		case MARIO_STATE_WALK_RIGHT:
			velocity.x = MARIO_WALKING_SPEED;
			direction = 1;
			break;
		case MARIO_STATE_WALK_LEFT:
			velocity.x = -MARIO_WALKING_SPEED;
			direction = -1;
			break;
		case MARIO_STATE_JUMP:
			if (position.y == 100)
				velocity.y = -MARIO_JUMP_SPEED_Y;
		case MARIO_STATE_IDLE:
			velocity.x = 0;
			break;
	}
}

std::string Mario::GetAnimationState()
{
	if (velocity.x == 0)
	{
		if (direction > 0)
			return MARIO_IDLE_RIGHT;
		else
			return MARIO_IDLE_LEFT;
	}
	else if (velocity.x > 0)
	{
		return MARIO_WALK_RIGHT;
	}
	return MARIO_WALK_LEFT;
}

#pragma region INPUT HANDLER

void Mario::OnKeyDown(InputManager *inputManager, KeyEventArgs e)
{
	FileLogger::GetInstance().Info("KeyDown: " + std::to_string(e.KeyCode));
	switch (e.KeyCode)
	{
		case DIK_SPACE:
			SetState(MARIO_STATE_JUMP);
			break;
	}
}

void Mario::OnKeyUp(InputManager *inputManager, KeyEventArgs e)
{
	FileLogger::GetInstance().Info("KeyUp: " + std::to_string(e.KeyCode));
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