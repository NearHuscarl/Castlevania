#include "Direct2DGame/Utilities/FileLogger.h"
#include "Mario.h"
#include "MarioStates.h"

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
	switch (state)
	{
		case WALK_LEFT:
			velocity.x = -MARIO_WALKING_SPEED;
			direction = Left;
			break;

		case WALK_RIGHT:
			velocity.x = MARIO_WALKING_SPEED;
			direction = Right;
			break;

		case IDLE:
			velocity.x = 0;
			break;

		case JUMP:
			if (position.y == 100)
				velocity.y = -MARIO_JUMP_SPEED_Y;
			break;
	}

	GameObject::UpdateDistance(deltaTime);

	ResolveCollision();

	(*animations)[GetAnimation()].Update();
}

std::string Mario::GetAnimation()
{
	return STATE_TO_ANIMATION.at((State)state);
}

void Mario::ResolveCollision()
{
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
}

void Mario::Draw(ISpriteBatch_ spriteBatch)
{
	auto effects = direction == Left ? SpriteEffects::FlipHorizontally : SpriteEffects::None;
	(*animations)[GetAnimation()].Draw(spriteBatch, position, effects);
}

#pragma region INPUT HANDLER

void Mario::OnKeyDown(InputManager &inputManager, KeyEventArgs e)
{
	FileLogger::GetInstance().Info("KeyDown: " + std::to_string(e.KeyCode));
	switch (e.KeyCode)
	{
		case DIK_SPACE:
			SetState(JUMP);
			break;
	}
}

void Mario::OnKeyUp(InputManager &inputManager, KeyEventArgs e)
{
	FileLogger::GetInstance().Info("KeyUp: " + std::to_string(e.KeyCode));
}

void Mario::OnKeyState(InputManager &inputManager)
{
	if (inputManager.IsKeyDown(DIK_RIGHT))
	{
		SetState(WALK_RIGHT);
	}
	else if (inputManager.IsKeyDown(DIK_LEFT))
	{
		SetState(WALK_LEFT);
	}
	else
	{
		return SetState(IDLE);
	}
}

#pragma endregion