#include "GiantBatCollisionSystem.h"
#include "GiantBat.h"
#include "../../UpdateData.h"
#include "../../Settings.h"

using namespace Castlevania;

GiantBatCollisionSystem::GiantBatCollisionSystem(GiantBat &parent) : parent{ parent }
{
}

IGameObject &GiantBatCollisionSystem::GetParent()
{
	return parent;
}

void GiantBatCollisionSystem::Update(UpdateData &updateData)
{
	auto &body = parent.GetBody();

	if (!body.Enabled())
		return;

	auto &objectCollection = *updateData.objectCollection;
	auto playerBbox = (Rect)objectCollection.player->GetBoundingBox();

	auto attackZone = parent.GetAttackZone();
	auto isPlayerInAttackZone = attackZone.TouchesOrIntersects(playerBbox);

	if (wasPlayerInAttackZone != isPlayerInAttackZone)
	{
		if (isPlayerInAttackZone)
			parent.SendMessageToSystems(PLAYER_IN_RANGE);
		else
			parent.SendMessageToSystems(PLAYER_OUT_OF_RANGE);

		wasPlayerInAttackZone = isPlayerInAttackZone;
	}

	auto threatZone = parent.GetThreatZone();
	auto isPlayerInThreatZone = threatZone.TouchesOrIntersects(playerBbox);

	if (wasPlayerInThreatZone != isPlayerInThreatZone)
	{
		if (isPlayerInThreatZone)
			parent.SendMessageToSystems(PLAYER_IN_THREAT_ZONE);

		wasPlayerInThreatZone = isPlayerInThreatZone;
	}
}
