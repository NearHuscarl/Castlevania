#include "GroundResponseSystem.h"
#include "../../GameObject.h"
#include "../../Settings.h"

using namespace Castlevania;

GroundResponseSystem::GroundResponseSystem(GameObject &parent) : parent{ parent }
{
}

GameObject &GroundResponseSystem::GetParent()
{
	return parent;
}

void GroundResponseSystem::OnTouchingGround(CollisionData collisionData)
{
	ClampDistance_Y(collisionData);
}
