#include "Player.h"
#include "../../../Settings/Animations.h"

using namespace Castlevania;

constexpr auto BEND_KNEE_ON_JUMPING_Y = 330.0f;
constexpr auto STRETCH_LEG_ON_FALLING_Y = 200.0f;
constexpr auto JUMP_COOLDOWN = 400; // 0.4 seconds

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
	GameObject::Update(deltaTime, objectCollection);
	UpdateStates();

	sprite->Update();
	whip->Update(deltaTime, objectCollection);
}

void Player::UpdateStates()
{
	switch (moveState)
	{
		case MoveState::JUMPING:
			if (velocity.y > -BEND_KNEE_ON_JUMPING_Y && attackState == AttackState::INACTIVE)
				sprite->Play(JUMP_ANIMATION);
			if (velocity.y >= 0)
				moveState = MoveState::FALLING;
			break;

		case MoveState::FALLING:
			if (velocity.y > STRETCH_LEG_ON_FALLING_Y && attackState == AttackState::INACTIVE)
				sprite->Play(IDLE_ANIMATION);
			break;

		case MoveState::LANDING_HARD:
			if (jumpCooldown.ElapsedMilliseconds() >= JUMP_COOLDOWN)
			{
				Idle();
				jumpCooldown.Reset();
			}
			break;
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
			case MoveState::FALLING:
				Landing();
				break;

			case MoveState::DUCKING:
				Duck();
				break;
		}

		whip->Withdraw();
	}
}

void Player::Landing()
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
	velocity.x = 0.0f;
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

void Player::Land()
{
	if (velocity.y > 600.0f) // Falling down very fast, do a superhero landing
	{
		moveState = MoveState::LANDING_HARD;
		velocity = Vector2::Zero();
		jumpCooldown.Start();
		sprite->Play(DUCK_ANIMATION);
	}
	else
		Idle();

	if (attackState == AttackState::ATTACKING)
		velocity.x = 0; // Still keep attacking on the ground but not moving anymore
}

#pragma endregion