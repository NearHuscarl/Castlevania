#include "SpawnerCollisionSystem.h"
#include "../UpdateData.h"

using namespace Castlevania;

SpawnerCollisionSystem::SpawnerCollisionSystem(GameObject &parent) : parent { parent }
{
}

void SpawnerCollisionSystem::Update(UpdateData &updateData)
{
	auto &body = parent.GetBody();
	body.ClearCollisionData();

	if (!body.Enabled())
		return;

	auto player = updateData.player;
	auto spawnAreaBbox = parent.GetBoundingBox();

	if (player->GetBoundingBox().Intersects(spawnAreaBbox))
	{
		auto results = std::vector<CollisionResult>{};
	
		results.push_back(CollisionResult{ 0, Direction::None, *player });
		body.SetCollisionData(CollisionData{ results });
	}
}
