#include "Simon.h"
#include "../../Settings/Animations.h"

using namespace Castlevania;

// TODO: use collision detection instead of hardcode GROUND_POSITION_Y
constexpr auto GROUND_POSITION_Y = 307.0f;
// TODO: put into Body class
constexpr auto GRAVITY = 18.0f;
constexpr auto STRETCH_LEG_VELOCITY_Y = 200.0f;

Simon::Simon(EntityType type) : GameObject(type)
{
	whip = std::make_unique<Whip>(*this);
}

void Simon::SetFacing(Facing facing)
{
	this->facing = facing;
	whip->SetFacing(facing);
}

Facing Castlevania::Simon::GetFacing()
{
	return facing;
}

MoveState Castlevania::Simon::GetMoveState()
{
	return moveState;
}

AttackState Castlevania::Simon::GetAttackState()
{
	return attackState;
}

void Simon::LoadContent(ContentManager &content)
{
	auto animationFactory = content.Load<AnimationFactory>("Characters/Players/Simon.xml");
	sprite = std::make_unique<AnimatedSprite>(animationFactory);

	auto stats = content.Load<Dictionary>("CharacterStats/Simon.xml");
	speed = std::stof(stats->at("WalkSpeed"));
	jumpSpeed = std::stof(stats->at("JumpSpeed"));

	whip->LoadContent(content);

	Idle();
}

void Simon::Update(float deltaTime, ObjectCollection *objectCollection)
{
	GameObject::UpdateDistance(deltaTime);
	
	switch (moveState)
	{
		case MoveState::JUMPING:
			velocity.y = -jumpSpeed;
			moveState = MoveState::JUMPED;
			break;

		case MoveState::JUMPED:
			if (velocity.y > STRETCH_LEG_VELOCITY_Y && attackState == AttackState::INACTIVE)
				sprite->Play(IDLE_ANIMATION);

			UpdateJumpState();
			break;

		case MoveState::LANDING:
			UpdateJumpState();
			break;
	}

	switch (attackState)
	{
		case AttackState::ATTACKING:
			UpdateAttackState();
			break;
	}
}

void Simon::UpdateJumpState()
{
	velocity.y += GRAVITY;

	if (position.y > GROUND_POSITION_Y)
	{
		position.y = GROUND_POSITION_Y;
		velocity.y = 0;

		if (attackState == AttackState::INACTIVE)
			Idle();
		else // AttackState::ATTACKING
			velocity.x = 0; // Still keep attacking on the ground but not moving anymore
	}
}

void Simon::UpdateAttackState()
{
	if (sprite->AnimateComplete())
	{
		attackState = AttackState::INACTIVE;

		switch (moveState)
		{
			case MoveState::WALKING:
			case MoveState::IDLE:
				Idle();
				break;

			case MoveState::JUMPING:
			case MoveState::JUMPED:
				Land();
				break;

			case MoveState::DUCKING:
				Duck();
				break;
		}

		whip->Withdraw();
	}
}

void Simon::Land()
{
	moveState = MoveState::LANDING;
	sprite->Play(JUMP_ANIMATION);
}

void Simon::Draw(SpriteExtensions &spriteBatch)
{
	if (facing == Facing::Right)
		sprite->SetEffect(SpriteEffects::None);
	else
		sprite->SetEffect(SpriteEffects::FlipHorizontally);

	//spriteBatch.Draw(GetBoundingBox(), Color::Pink()); // TODO: remove debugging code
	sprite->Update();
	spriteBatch.Draw(*sprite, position);
	
	whip->Draw(spriteBatch);
}

#pragma region Commands

void Simon::Idle()
{
	moveState = MoveState::IDLE;
	velocity = Vector2::Zero();
	sprite->Play(IDLE_ANIMATION);
}

void Simon::WalkLeft()
{
	moveState = MoveState::WALKING;
	SetFacing(Facing::Left);
	velocity.x = -speed;
	sprite->Play(WALK_ANIMATION);
}

void Simon::WalkRight()
{
	moveState = MoveState::WALKING;
	SetFacing(Facing::Right);
	velocity.x = speed;
	sprite->Play(WALK_ANIMATION);
}

void Simon::Jump()
{
	moveState = MoveState::JUMPING;
	sprite->Play(JUMP_ANIMATION);
}

void Simon::Duck()
{
	moveState = MoveState::DUCKING;
	velocity = Vector2::Zero();
	sprite->Play(DUCK_ANIMATION);
}

void Simon::Attack()
{
	attackState = AttackState::ATTACKING;

	switch (moveState)
	{
		case MoveState::WALKING:
			velocity = Vector2::Zero();
			sprite->Play(ATTACK_ANIMATION);
			break;

		case MoveState::IDLE:
			sprite->Play(ATTACK_ANIMATION);
			break;

		case MoveState::JUMPED:
		case MoveState::LANDING:
			sprite->Play(JUMP_ATTACK_ANIMATION);
			break;

		case MoveState::DUCKING:
			sprite->Play(DUCK_ATTACK_ANIMATION);
			break;

		default:
			return;
	}

	whip->Unleash();
}

void Simon::TurnBackward()
{
	moveState = MoveState::TURNING_BACKWARD;
	velocity = Vector2::Zero();
	sprite->Play(TURN_BACKWARD_ANIMATION);
}

#pragma endregion