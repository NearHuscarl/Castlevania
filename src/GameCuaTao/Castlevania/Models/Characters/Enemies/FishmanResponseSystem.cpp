#include "FishmanResponseSystem.h"

using namespace Castlevania;

FishmanResponseSystem::FishmanResponseSystem(Fishman &parent) : parent{ parent }
{
}

GameObject &FishmanResponseSystem::GetParent()
{
	return parent;
}

void FishmanResponseSystem::OnTouchingGround(CollisionData collisionData)
{
	ClampDistance_Y(collisionData);
}

void FishmanResponseSystem::OnFalling()
{
	parent.Freeze();
}

void FishmanResponseSystem::OnLanding()
{
	parent.Land();
}
