#include "Direct2DGame/MathHelper.h"
#include "PlayerMovementSystem.h"
#include "PlayerSettings.h"
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

void PlayerMovementSystem::Receive(int message)
{
	if (message == START_FALLING)
	{
		auto moveState = parent.GetMoveState();

		if (moveState == MoveState::WALKING
			|| moveState == MoveState::IDLE)
			parent.moveState = MoveState::FALLING_HARD;
	}
}

void PlayerMovementSystem::Update(GameTime gameTime)
{
	auto velocity = parent.GetVelocity();
	auto deltaTime = (float)gameTime.ElapsedGameTime.Seconds();
	auto moveState = parent.GetMoveState();

	if (moveState != MoveState::GOING_UPSTAIRS
		&& moveState != MoveState::GOING_DOWNSTAIRS
		&& moveState != MoveState::IDLE_UPSTAIRS
		&& moveState != MoveState::IDLE_DOWNSTAIRS)
		velocity.y = MathHelper::Min(velocity.y + GRAVITY, FALL_SPEED);
	
	parent.SetVelocity(velocity);

	distance = velocity * deltaTime;
}
