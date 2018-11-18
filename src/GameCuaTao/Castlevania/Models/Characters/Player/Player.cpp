#include "Player.h"
#include "../../../Settings/Animations.h"

using namespace Castlevania;

constexpr auto STRETCH_LEG_VELOCITY_Y = 200.0f;

Player::Player() : GameObject(EntityType::Player)
{
	this->whip = std::make_unique<Whip>(*this);
}

void Player::SetFacing(Facing facing)
{
	this->facing = facing;
	whip->SetFacing(facing);
}

Facing Player::GetFacing()
{
	return facing;
}

MoveState Player::GetMoveState()
{
	return moveState;
}

AttackState Player::GetAttackState()
{
	return attackState;
}

// NOTE: revert or not
void Player::SetVelocity(Vector2 velocity)
{
	//if (velocity == Vector2::Zero())
	//	Idle();

	this->velocity = velocity;
}

void Player::LoadContent(ContentManager &content)
{
	auto animationFactory = content.Load<AnimationFactory>("Characters/Players/Simon.xml");
	sprite = std::make_unique<AnimatedSprite>(animationFactory);

	auto stats = content.Load<Dictionary>("CharacterStats/Simon.xml");
	speed = std::stof(stats->at("WalkSpeed"));
	jumpSpeed = std::stof(stats->at("JumpSpeed"));

	whip->LoadContent(content);

	Idle();
}

void Player::Update(float deltaTime, ObjectCollection *objectCollection)
{
	UpdateStates();
	GameObject::Update(deltaTime, objectCollection);

	sprite->Update();
	whip->Update(deltaTime, objectCollection);
}

void Player::UpdateStates()
{
	switch (moveState)
	{
		case MoveState::JUMPING:
			if (velocity.y > STRETCH_LEG_VELOCITY_Y && attackState == AttackState::INACTIVE)
				sprite->Play(IDLE_ANIMATION);
	}

	switch (attackState)
	{
		case AttackState::ATTACKING:
			UpdateAttackState();
			break;
	}
}

void Player::UpdateAttackState()
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
				Land();
				break;

			case MoveState::DUCKING:
				Duck();
				break;
		}

		whip->Withdraw();
	}
}

void Player::Land()
{
	moveState = MoveState::LANDING;
	sprite->Play(JUMP_ANIMATION);
}

void Player::Draw(SpriteExtensions &spriteBatch)
{
	if (facing == Facing::Right)
		sprite->SetEffect(SpriteEffects::None);
	else
		sprite->SetEffect(SpriteEffects::FlipHorizontally);

	spriteBatch.Draw(*sprite, position);
	
	whip->Draw(spriteBatch);
}

void Player::DrawBoundingBox(SpriteExtensions &spriteBatch)
{
	GameObject::DrawBoundingBox(spriteBatch);
	whip->DrawBoundingBox(spriteBatch);
}

#pragma region Commands

void Player::Idle()
{
	moveState = MoveState::IDLE;
	velocity = Vector2::Zero();
	sprite->Play(IDLE_ANIMATION);
}

void Player::WalkLeft()
{
	moveState = MoveState::WALKING;
	SetFacing(Facing::Left);
	velocity.x = -speed;
	sprite->Play(WALK_ANIMATION);
}

void Player::WalkRight()
{
	moveState = MoveState::WALKING;
	SetFacing(Facing::Right);
	velocity.x = speed;
	sprite->Play(WALK_ANIMATION);
}

void Player::Jump()
{
	velocity.y = -jumpSpeed;
	moveState = MoveState::JUMPING;
	sprite->Play(JUMP_ANIMATION);
}

void Player::Duck()
{
	moveState = MoveState::DUCKING;
	velocity = Vector2::Zero();
	sprite->Play(DUCK_ANIMATION);
}

void Player::Attack()
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

		case MoveState::JUMPING:
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

void Player::TurnBackward()
{
	moveState = MoveState::TURNING_BACKWARD;
	velocity = Vector2::Zero();
	sprite->Play(TURN_BACKWARD_ANIMATION);
}

#pragma endregion