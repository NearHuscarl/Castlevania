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

MoveState Castlevania::Simon::GetMoveState()
{
	return moveState;
}

AttackState Castlevania::Simon::GetAttackState()
{
	return attackState;
}

void Simon::SetNextMoveState(MoveState state)
{
	nextMoveState = state;
}

void Simon::LoadContent(ContentManager &content)
{
	auto animationFactory = content.Load<AnimationFactory>("Characters/Players/Simon.xml");
	sprite = std::make_unique<AnimatedSprite>(animationFactory);

	auto stats = content.Load<CharacterStats>("CharacterStats/Simon.xml");
	speed = std::stof(stats->at("WalkSpeed"));
	jumpSpeed = std::stof(stats->at("JumpSpeed"));

	whip->LoadContent(content);

	Idle();
}

void Simon::Update(float deltaTime)
{
	GameObject::UpdateDistance(deltaTime);
	
	switch (moveState)
	{
		case MoveState::JUMPING:
			velocity.y = -jumpSpeed;
			moveState = MoveState::JUMPED;
			break;

		case MoveState::JUMPED:
			velocity.y += GRAVITY;
			
			if (velocity.y > STRETCH_LEG_VELOCITY_Y && attackState == AttackState::INACTIVE)
				sprite->Play(IDLE_ANIMATION);

			if (position.y > GROUND_POSITION_Y)
			{
				position.y = GROUND_POSITION_Y;
				velocity.y = 0;
				Idle();
			}
			break;
	}

	switch (attackState)
	{
		case AttackState::ATTACKING:
			Attacking();
			break;
	}
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
	moveState = MoveState::WALKING_LEFT;
	SetFacing(Facing::Left);
	velocity.x = -speed;
	sprite->Play(WALK_ANIMATION);
}

void Simon::WalkRight()
{
	moveState = MoveState::WALKING_RIGHT;
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
	nextMoveState = moveState;

	if (moveState == MoveState::WALKING_LEFT || moveState == MoveState::WALKING_RIGHT)
	{
		velocity = Vector2::Zero();
		sprite->Play(ATTACK_ANIMATION);
	}
	else if (moveState == MoveState::IDLE)
		sprite->Play(ATTACK_ANIMATION);
	else if (moveState == MoveState::JUMPED)
		sprite->Play(JUMP_ATTACK_ANIMATION);
	else if (moveState == MoveState::DUCKING)
		sprite->Play(DUCK_ATTACK_ANIMATION);
	else
		return;

	whip->Unleash();
}

void Simon::Attacking()
{
	if (sprite->AnimateComplete())
	{
		attackState = AttackState::INACTIVE;
		moveState = nextMoveState;

		if (moveState == MoveState::WALKING_LEFT
			|| moveState == MoveState::WALKING_RIGHT
			|| moveState == MoveState::IDLE)
			Idle();
		else if (moveState == MoveState::JUMPING)
			moveState = MoveState::JUMPED;
		else if (moveState == MoveState::DUCKING)
			Duck();

		whip->Withdraw();
	}
}

void Simon::TurnBackward()
{
	moveState = MoveState::TURNING_BACKWARD;
	velocity = Vector2::Zero();
	sprite->Play(TURN_BACKWARD_ANIMATION);
}

#pragma endregion