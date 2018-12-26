#include "Powerup.h"

using namespace Castlevania;

constexpr auto DEFAULT_POWERUP_LIFESPAN = 4000; // in milliseconds

Powerup::Powerup(ObjectId type, int lifeSpan) : GameObject{ type }
{
	if (lifeSpan == 0)
		this->lifeSpan = DEFAULT_POWERUP_LIFESPAN;
	else
		this->lifeSpan = lifeSpan;
}

void Powerup::Spawn()
{
	lifespanTimer.Start();
}

void Powerup::Update(UpdateData &updateData)
{
	GameObject::Update(updateData);

	// Powerup self-destruct after a given amount of time
	if (lifespanTimer.ElapsedMilliseconds() >= lifeSpan)
		Destroy();
}
