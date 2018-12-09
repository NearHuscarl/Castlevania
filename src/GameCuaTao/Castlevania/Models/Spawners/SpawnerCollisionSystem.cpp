#include "SpawnerCollisionSystem.h"
#include "../Factories/ObjectCollection.h"

using namespace Castlevania;

SpawnerCollisionSystem::SpawnerCollisionSystem(GameObject &parent) : parent { parent }
{
}

void SpawnerCollisionSystem::Update(ObjectCollection &objectCollection)
{
	auto &body = parent.GetBody();
	body.ClearCollisionData();

	if (!body.Enabled())
		return;

	auto player = objectCollection.player;
	auto spawnAreaBbox = parent.GetBoundingBox();

	if (player->GetBoundingBox().Intersects(spawnAreaBbox))
	{
		auto results = std::vector<CollisionResult>{};
	
		results.push_back(CollisionResult{ 0, Direction::None, *player });
		body.SetCollisionData(CollisionData{ results });
	}
}
