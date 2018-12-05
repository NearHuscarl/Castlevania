#include "ZombieResponseSystem.h"

using namespace Castlevania;

ZombieResponseSystem::ZombieResponseSystem(Zombie &parent) : parent{ parent }
{
}

GameObject &ZombieResponseSystem::GetParent()
{
	return parent;
}

void ZombieResponseSystem::OnTouchingGround(CollisionData collisionData)
{
	ClampDistance_Y(collisionData);
}

void ZombieResponseSystem::OnFalling()
{
	parent.StopWalking();
}

void ZombieResponseSystem::OnLanding()
{
	parent.Land();
}
