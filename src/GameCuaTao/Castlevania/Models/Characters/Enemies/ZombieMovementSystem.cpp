#include "ZombieMovementSystem.h"

using namespace Castlevania;

ZombieMovementSystem::ZombieMovementSystem(Zombie &parent) : parent{ parent }
{
}

void ZombieMovementSystem::Update(GameTime gameTime)
{
	auto velocity = parent.GetVelocity();
	auto deltaTime = (float)gameTime.ElapsedGameTime.Seconds();

	distance = velocity * deltaTime;
}
