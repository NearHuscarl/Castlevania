#include "EntityCollisionSystem.h"
#include "../../GameObject.h"
#include "../../../Models/Factories/ObjectCollection.h"

using namespace Castlevania;

EntityCollisionSystem::EntityCollisionSystem(GameObject &parent) : parent{ parent }
{
}

IGameObject &EntityCollisionSystem::GetParent()
{
	return parent;
}

void EntityCollisionSystem::Update(ObjectCollection &objectCollection)
{
	auto &body = parent.GetBody();
	body.ClearCollisionData();

	if (!body.Enabled())
		return;

	auto results = std::vector<CollisionResult>{};
	auto &entities = objectCollection.entities;

	for (auto &entity : entities)
	{
		CalculateCollision(*entity, results);
	}

	// TODO: do we need to sort?
	body.SetCollisionData(FilterCollision(results));
}
