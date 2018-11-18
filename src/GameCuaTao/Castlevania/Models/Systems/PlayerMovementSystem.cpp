#include "PlayerMovementSystem.h"
#include "../GameObject.h"

using namespace Castlevania;

PlayerMovementSystem::PlayerMovementSystem(Player &parent) : parent{ parent }
{
}

Vector2 PlayerMovementSystem::GetDistance()
{
	return distance;
}

void PlayerMovementSystem::Update(float deltaTime)
{
	auto velocity = parent.GetVelocity();
	auto moveState = parent.GetMoveState();

	if (moveState == MoveState::JUMPING
		|| moveState == MoveState::LANDING
		|| moveState == MoveState::FALLING)
	{
		velocity.y += GRAVITY;
	}
	else
	{
		if (!parent.isOnGround)
			parent.moveState = MoveState::FALLING_HARD;

		velocity.y = FALL_SPEED;
	}

	distance = velocity * deltaTime;

	parent.SetVelocity(velocity);
}
