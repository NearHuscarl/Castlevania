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

void MovementSystem::Update(float deltaTime)
{
	auto velocity = parent.GetVelocity();

	distance = velocity * deltaTime;
}
