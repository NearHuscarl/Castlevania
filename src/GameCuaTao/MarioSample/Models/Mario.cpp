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
	Idle();
}

void Mario::UpdateInput()
{
	switch (state)
	{
		case IDLE:
			if (InputHelper::IsKeyDown(DIK_SPACE))
				Jump();
			if (InputHelper::IsKeyPressed(DIK_RIGHT))
				WalkRight();
			else if (InputHelper::IsKeyPressed(DIK_LEFT))
				WalkLeft();
			break;

		case WALK_LEFT:
			if (InputHelper::IsKeyDown(DIK_SPACE))
				Jump();
			else if (InputHelper::IsKeyUp(DIK_LEFT))
				Idle();
			break;

		case WALK_RIGHT:
			if (InputHelper::IsKeyDown(DIK_SPACE))
				Jump();
			else if (InputHelper::IsKeyUp(DIK_RIGHT))
				Idle();
			break;

		case JUMP:
			Jump();
			break;
	}
}

void Mario::Update(float deltaTime)
{
	UpdateInput();

	GameObject::UpdateDistance(deltaTime);

	ResolveCollision();

	(*animations)[currentAnimation].Update();
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
	if (GetState() == JUMP)
	{
		if (position.y == 100)
			velocity.y = -MARIO_JUMP_SPEED_Y;
		else
			SetState(IDLE);
	}
	else
	{
		SetState(JUMP);
		if (position.y == 100)
			AudioManager::Play("Jump");
	}
}

void Mario::Idle()
{
	SetState(IDLE);
	velocity.x = 0;
	currentAnimation = MARIO_IDLE;
}

void MarioSample::Mario::WalkLeft()
{
	SetState(WALK_LEFT);
	velocity.x = -MARIO_WALKING_SPEED;
	direction = Left;
	currentAnimation = MARIO_WALK;
}

void MarioSample::Mario::WalkRight()
{
	SetState(WALK_RIGHT);
	velocity.x = MARIO_WALKING_SPEED;
	direction = Right;
	currentAnimation = MARIO_WALK;
}

void Mario::Draw(SpriteBatch &spriteBatch)
{
	auto effects = direction == Left ? SpriteEffects::FlipHorizontally : SpriteEffects::None;
	(*animations)[currentAnimation].Draw(spriteBatch, position, Color::White(), effects);
}