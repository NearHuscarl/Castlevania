#include "MovementSystem.h"
#include "../GameObject.h"

using namespace Castlevania;

MovementSystem::MovementSystem(GameObject &parent) : parent{ parent }
{
}

Vector2 MovementSystem::GetDistance()
{
	return distance;
}

void MovementSystem::Update()
{
	auto deltaTime = parent.GetBody().GetDeltaTime();
	auto velocity = parent.GetVelocity();

	distance = velocity * deltaTime;
}
