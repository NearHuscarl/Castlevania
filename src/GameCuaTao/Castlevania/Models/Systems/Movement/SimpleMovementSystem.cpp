#include "SimpleMovementSystem.h"
#include "../../GameObject.h"

using namespace Castlevania;

SimpleMovementSystem::SimpleMovementSystem(GameObject &parent) : parent{ parent }
{
}

void SimpleMovementSystem::Update(GameTime gameTime)
{
	auto velocity = parent.GetVelocity();
	auto deltaTime = (float)gameTime.ElapsedGameTime.Seconds();

	distance = velocity * deltaTime;
}
