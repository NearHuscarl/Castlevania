#include "StaticCollisionSystem.h"
#include "../../GameObject.h"
#include "../../../Models/UpdateData.h"

using namespace Castlevania;

StaticCollisionSystem::StaticCollisionSystem(GameObject &parent) : parent{ parent }
{
}

IGameObject &StaticCollisionSystem::GetParent()
{
	return parent;
}

void StaticCollisionSystem::Update(UpdateData &updateData)
{
	auto &body = parent.GetBody();
	body.ClearCollisionData();

	if (!body.Enabled())
		return;

	auto results = std::vector<CollisionResult>{};
	auto &boundaries = updateData.objectCollection->boundaries;

	for (auto &boundary : boundaries)
	{
		CalculateCollision(*boundary, results);
	}

	// TODO: do we need to sort?
	body.SetCollisionData(FilterCollision(results));
}
