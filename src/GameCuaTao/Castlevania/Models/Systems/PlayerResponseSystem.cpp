#include "PlayerResponseSystem.h"

using namespace Castlevania;

PlayerResponseSystem::PlayerResponseSystem(Player &parent) :
	CollisionResponseSystem{ parent },
	parent{ parent }
{
}

void PlayerResponseSystem::Update(float deltaTime, CollisionData collisionData)
{
	CollisionResponseSystem::Update(deltaTime, collisionData);
}
