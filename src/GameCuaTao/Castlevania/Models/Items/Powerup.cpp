#include "Powerup.h"

using namespace Castlevania;

constexpr auto LIFESPAN = 4000; // in milliseconds

Powerup::Powerup(EntityType type) : GameObject{ type }
{
}

void Powerup::Spawn()
{
	lifespanTimer.Start();
}

void Powerup::Update(GameTime gameTime, UpdateData &updateData)
{
	GameObject::Update(gameTime, updateData);

	// Powerup self-destruct after a given amount of time
	if (lifespanTimer.ElapsedMilliseconds() >= LIFESPAN)
		Destroy();
}
