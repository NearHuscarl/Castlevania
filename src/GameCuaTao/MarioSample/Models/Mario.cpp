#include "Direct2DGame/Utilities/FileLogger.h"
#include "Mario.h"
#include "MarioSettings.h"
#include "Direct2DGame/Input/InputHelper.h"
#include "../Utilities/AudioManager.h"

using namespace MarioSample;

void Mario::LoadContent(ContentManager &content)
{
	auto animationFactory = content.Load<AnimationFactory>("MarioAnimationDef.xml");
	sprite = std::make_unique<AnimatedSprite>(animationFactory);
	SetPosition(0.0f, 100.0f);
	Idle();
}

void Mario::Update(float deltaTime)
{
	UpdateInput();
	UpdateState();

	ResolveCollision(deltaTime);

	sprite->Update(deltaTime);
}

void Mario::UpdateInput()
{
	switch (state)
	{
		case State::IDLE:
			if (InputHelper::IsKeyDown(DIK_SPACE))
				Jump();
			if (InputHelper::IsKeyPressed(DIK_RIGHT))
				WalkRight();
			else if (InputHelper::IsKeyPressed(DIK_LEFT))
				WalkLeft();
			break;

		case State::WALKING_LEFT:
			if (InputHelper::IsKeyDown(DIK_SPACE))
				Jump();
			if (!InputHelper::IsKeyPressed(DIK_LEFT))
				Idle();
			break;

		case State::WALKING_RIGHT:
			if (InputHelper::IsKeyDown(DIK_SPACE))
				Jump();
			if (!InputHelper::IsKeyPressed(DIK_RIGHT))
				Idle();
			break;
	}
}

void Mario::UpdateState()
{
	switch (state)
	{
		case State::JUMPING:
			Jumping();
			break;
	}
}

void Mario::ResolveCollision(float deltaTime)
{
	GameObject::UpdateDistance(deltaTime);

	// simple fall down
	velocity.y += MARIO_GRAVITY;
	if (position.y > 100)
	{
		velocity.y = 0;
		position.y = 100.0f;
	}

	// simple screen edge collision!!!
	if (velocity.x > 0 && position.x > 305)
	{
		position.x = 305;
	}
	if (velocity.x < 0 && position.x < 0)
	{
		position.x = 0;
	}
}

void Mario::Jump()
{
	state = State::JUMPING;
}

void Mario::Jumping()
{
	if (position.y == 100)
	{
		AudioManager::Play("Jump");
		velocity.y = -MARIO_JUMP_SPEED_Y;
	}
	else
		state = State::IDLE;
}

void Mario::Idle()
{
	state = State::IDLE;
	velocity.x = 0;
	sprite->Play(MARIO_IDLE);
}

void Mario::WalkLeft()
{
	state = State::WALKING_LEFT;
	velocity.x = -MARIO_WALKING_SPEED;
	direction = Direction::Left;
	sprite->Play(MARIO_WALK);
}

void Mario::WalkRight()
{
	state = State::WALKING_RIGHT;
	velocity.x = MARIO_WALKING_SPEED;
	direction = Direction::Right;
	sprite->Play(MARIO_WALK);
}

void Mario::Draw(SpriteBatch &spriteBatch)
{
	auto effect = direction == Direction::Left ? SpriteEffects::FlipHorizontally : SpriteEffects::None;
	auto &texture = sprite->GetTextureRegion().GetTexture();
	auto srcRectangle = sprite->GetTextureRegion().GetFrameRectangle();

	spriteBatch.Draw(texture, position, &srcRectangle, Color::White(), 0.0f, Vector2::One(), effect);
}