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

	velocity.y += GRAVITY;

	distance = velocity * deltaTime;

	parent.SetVelocity(velocity);
}
