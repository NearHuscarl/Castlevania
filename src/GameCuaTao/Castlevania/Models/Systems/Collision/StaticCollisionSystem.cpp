#include "StaticCollisionSystem.h"
#include "../../GameObject.h"
#include "../../../Models/Factories/ObjectCollection.h"

using namespace Castlevania;

StaticCollisionSystem::StaticCollisionSystem(GameObject &parent) : parent{ parent }
{
}

IGameObject &StaticCollisionSystem::GetParent()
{
	return parent;
}

void StaticCollisionSystem::Update(ObjectCollection &objectCollection)
{
	auto &body = parent.GetBody();

	if (!body.Enabled())
	{
		body.ClearCollisionData();
		return;
	}

	auto results = std::vector<CollisionResult>{};
	auto &boundaries = objectCollection.boundaries;

	for (auto &boundary : boundaries)
	{
		CalculateCollision(*boundary, results);
	}

	// TODO: do we need to sort?
	body.SetCollisionData(FilterCollision(results));
}
