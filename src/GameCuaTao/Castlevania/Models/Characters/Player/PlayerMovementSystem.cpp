#include "PlayerMovementSystem.h"
#include "../../GameObject.h"

using namespace Castlevania;

constexpr auto FALL_SPEED = 1000.0f; // TODO: put in xml

PlayerMovementSystem::PlayerMovementSystem(Player &parent) : parent{ parent }
{
}

Vector2 PlayerMovementSystem::GetDistance()
{
	return distance;
}

void PlayerMovementSystem::SetDistance(Vector2 distance)
{
	this->distance = distance;
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
	parent.SetVelocity(velocity);

	distance = velocity * deltaTime;
}
