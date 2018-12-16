#include "GiantBatCollisionSystem.h"
#include "GiantBat.h"
#include "../../Factories/ObjectCollection.h"
#include "../../Settings.h"

using namespace Castlevania;

GiantBatCollisionSystem::GiantBatCollisionSystem(GiantBat &parent) : parent{ parent }
{
}

IGameObject &GiantBatCollisionSystem::GetParent()
{
	return parent;
}

void GiantBatCollisionSystem::Update(ObjectCollection &objectCollection)
{
	auto &body = parent.GetBody();

	if (!body.Enabled())
		return;

	auto playerBbox = (Rect)objectCollection.player->GetBoundingBox();
	auto attackZone = parent.GetAttackArea();

	if (!parent.IsInRange())
	{
		if (attackZone.TouchesOrIntersects(playerBbox))
		{
			parent.SendMessageToSystems(PLAYER_IN_RANGE);
		}
	}
	else // (parent.IsInRange())
	{
		if (!attackZone.TouchesOrIntersects(playerBbox))
		{
			parent.SendMessageToSystems(PLAYER_OUT_OF_RANGE);
		}
	}
}
