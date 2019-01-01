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
	if (!parent.GetBody().Enabled())
		return;

	auto playerBbox = (Rect)updateData.player->GetBoundingBox();

	CheckZonesCollision(playerBbox);
}

void GiantBatCollisionSystem::CheckZonesCollision(Rect playerBbox)
{
	auto attackZone = parent.GetAttackZone();
	auto isPlayerInAttackZone = attackZone.TouchesOrIntersects(playerBbox);

	if (isPlayerInAttackZone != wasPlayerInAttackZone)
	{
		if (isPlayerInAttackZone)
			parent.SendMessageToSystems(PLAYER_IN_RANGE);
		else
			parent.SendMessageToSystems(PLAYER_OUT_OF_RANGE);

		wasPlayerInAttackZone = isPlayerInAttackZone;
	}

	auto threatZone = parent.GetThreatZone();
	auto isPlayerInThreatZone = threatZone.TouchesOrIntersects(playerBbox);

	if (isPlayerInThreatZone != wasPlayerInThreatZone)
	{
		if (isPlayerInThreatZone)
			parent.SendMessageToSystems(PLAYER_IN_THREAT_ZONE);

		wasPlayerInThreatZone = isPlayerInThreatZone;
	}
}
