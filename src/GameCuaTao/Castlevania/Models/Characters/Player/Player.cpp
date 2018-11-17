#include "Player.h"
#include "../../../Settings/Animations.h"

using namespace Castlevania;

// TODO: use collision detection instead of hardcode GROUND_POSITION_Y
constexpr auto GROUND_POSITION_Y = 307.0f;
// TODO: put into Body class
constexpr auto GRAVITY = 18.0f;
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

void Player::SetController(std::unique_ptr<IController> controller)
{
	this->controller = std::move(controller);
}

IController *Player::GetController()
{
	return controller.get();
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
	GameObject::Update(deltaTime);
	UpdateStates();
	collisionSystem->Update(deltaTime, *objectCollection);
	collisionResponseSystem->Update(deltaTime, collisionSystem->GetCollisionData());
}

void Player::UpdateStates()
{
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

void Player::UpdateJumpState()
{
	if (velocity.y == 0) // Touch ground
	{
		if (attackState == AttackState::INACTIVE)
			Idle();
		else // AttackState::ATTACKING
			velocity.x = 0; // Still keep attacking on the ground but not moving anymore
	}
	else
		velocity.y += GRAVITY;

	//if (position.y > GROUND_POSITION_Y)
	//{
	//	position.y = GROUND_POSITION_Y;
	//	velocity.y = 0;

	//	if (attackState == AttackState::INACTIVE)
	//		Idle();
	//	else // AttackState::ATTACKING
	//		velocity.x = 0; // Still keep attacking on the ground but not moving anymore
	//}
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

	spriteBatch.Draw(GetBoundingBox(), Color::Pink()); // TODO: remove debugging code
	sprite->Update();
	spriteBatch.Draw(*sprite, position);
	
	whip->Draw(spriteBatch);
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

void Player::TurnBackward()
{
	moveState = MoveState::TURNING_BACKWARD;
	velocity = Vector2::Zero();
	sprite->Play(TURN_BACKWARD_ANIMATION);
}

#pragma endregion