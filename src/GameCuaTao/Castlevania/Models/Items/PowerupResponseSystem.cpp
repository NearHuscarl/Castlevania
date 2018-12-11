#include "PowerupResponseSystem.h"
#include "../GameObject.h"

using namespace Castlevania;

PowerupResponseSystem::PowerupResponseSystem(GameObject &parent) : parent{ parent }
{
}

GameObject &PowerupResponseSystem::GetParent()
{
	return parent;
}

void PowerupResponseSystem::OnTouchingGround(CollisionData collisionData)
{
	ClampDistance_Y(collisionData);
	parent.SetDistance_X(0.0f);
}
