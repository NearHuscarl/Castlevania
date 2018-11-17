#include "PlayerResponseSystem.h"

using namespace Castlevania;

PlayerResponseSystem::PlayerResponseSystem(Player &parent) :
	CollisionResponseSystem{ parent },
	parent{ parent }
{
}

void PlayerResponseSystem::Update(CollisionData collisionData)
{
	CollisionResponseSystem::Update(collisionData);
}
