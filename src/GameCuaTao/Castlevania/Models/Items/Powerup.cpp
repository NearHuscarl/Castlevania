#include "Powerup.h"

using namespace Castlevania;

constexpr auto LIFESPAN = 4000; // in milliseconds

Powerup::Powerup(EntityType type) : GameObject(type)
{
}

void Powerup::Spawn()
{
	lifespanTimer.Start();
}

void Powerup::Update(float deltaTime, ObjectCollection *objectCollection)
{
	GameObject::Update(deltaTime, objectCollection);

	// Powerup self-destruct after a given amount of time
	if (lifespanTimer.ElapsedMilliseconds() >= LIFESPAN)
		Destroy();
}
