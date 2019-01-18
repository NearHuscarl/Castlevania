#include "MovementSystem.h"
#include "../../GameObject.h"

using namespace Castlevania;

MovementSystem::MovementSystem()
{
	enabled = true;
}

void MovementSystem::Enabled(bool value)
{
	enabled = value;
}

bool MovementSystem::Enabled()
{
	return enabled;
}

Vector2 MovementSystem::GetDistance()
{
	return distance;
}

void MovementSystem::SetDistance(Vector2 distance)
{
	this->distance = distance;
}

void MovementSystem::Update(GameTime gameTime)
{
	if (enabled)
		UpdateMovement(gameTime);
}
