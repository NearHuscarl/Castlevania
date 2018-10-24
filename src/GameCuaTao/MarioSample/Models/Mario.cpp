#include "Direct2DGame/Utilities/FileLogger.h"
#include "Mario.h"
#include "MarioStates.h"
#include "Direct2DGame/Input/InputHelper.h"
#include "../Utilities/AudioManager.h"

using namespace MarioSample;

constexpr auto MARIO_WALKING_SPEED = 50.f;
constexpr auto MARIO_JUMP_SPEED_Y = 700.f;
constexpr auto MARIO_GRAVITY = 50.f;

void Mario::LoadContent(ContentManager &content)
{
	animations = content.Load<AnimationDict>("MarioAnimationDef.xml");
	SetPosition(0.0f, 100.0f);
	SetState(IDLE);
}

void MarioSample::Mario::UpdateInput()
{
	switch (state)
	{
		case IDLE:
			if (InputHelper::IsKeyDown(DIK_SPACE))
				Jump();
			if (InputHelper::IsKeyPressed(DIK_RIGHT))
				SetState(WALK_RIGHT);
			else if (InputHelper::IsKeyPressed(DIK_LEFT))
				SetState(WALK_LEFT);
			break;

		case WALK_LEFT:
		case WALK_RIGHT:
			if (InputHelper::IsKeyDown(DIK_SPACE))
				Jump();
			else if (InputHelper::IsKeyUp(DIK_LEFT))
				SetState(IDLE);
			else if (InputHelper::IsKeyUp(DIK_RIGHT))
				SetState(IDLE);
			break;
	}
}

void Mario::Update(float deltaTime)
{
	UpdateInput();

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
			else
				SetState(IDLE);
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
	{
		position.x = 290;
	}
	if (velocity.x < 0 && position.x < 0)
	{
		position.x = 0;
	}
}

void Mario::Jump()
{
	SetState(JUMP);
	if (position.y == 100)
		AudioManager::Play("Jump");
}

void Mario::Draw(SpriteBatch &spriteBatch)
{
	auto effects = direction == Left ? SpriteEffects::FlipHorizontally : SpriteEffects::None;
	(*animations)[GetAnimation()].Draw(spriteBatch, position, Color::White(), effects);
}