#include "MovementSystem.h"
#include "../../GameObject.h"

using namespace Castlevania;

Vector2 MovementSystem::GetDistance()
{
	return distance;
}

void MovementSystem::SetDistance(Vector2 distance)
{
	this->distance = distance;
}
