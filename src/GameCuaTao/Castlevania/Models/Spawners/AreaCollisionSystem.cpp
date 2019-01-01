#include "AreaCollisionSystem.h"
#include "../UpdateData.h"
#include "../Settings.h"

using namespace Castlevania;

AreaCollisionSystem::AreaCollisionSystem(GameObject &parent) : parent { parent }
{
}

void AreaCollisionSystem::Update(UpdateData &updateData)
{
	auto &body = parent.GetBody();
	body.ClearCollisionData();

	if (!body.Enabled())
		return;

	auto playerBbox = updateData.player->GetBoundingBox();
	auto spawnAreaBbox = parent.GetBoundingBox();
	auto isPlayerInSpawnZone = spawnAreaBbox.TouchesOrIntersects(playerBbox);

	if (isPlayerInSpawnZone != wasPlayerInSpawnZone)
	{
		if (isPlayerInSpawnZone)
			parent.SendMessageToSystems(PLAYER_IN_RANGE);
		else
			parent.SendMessageToSystems(PLAYER_OUT_OF_RANGE);

		wasPlayerInSpawnZone = isPlayerInSpawnZone;
	}
}
