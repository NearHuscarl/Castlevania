#include "EntityCollisionSystem.h"
#include "../../GameObject.h"
#include "../../../Models/UpdateData.h"

using namespace Castlevania;

EntityCollisionSystem::EntityCollisionSystem(GameObject &parent) : parent{ parent }
{
}

IGameObject &EntityCollisionSystem::GetParent()
{
	return parent;
}

void EntityCollisionSystem::Update(UpdateData &updateData)
{
	auto &body = parent.GetBody();
	body.ClearCollisionData();

	if (!body.Enabled())
		return;

	auto results = std::vector<CollisionResult>{};
	auto &entities = updateData.objectCollection->entities;

	for (auto &entity : entities)
	{
		CalculateCollision(*entity, results);
	}

	// TODO: do we need to sort?
	body.SetCollisionData(FilterCollision(results));
}
