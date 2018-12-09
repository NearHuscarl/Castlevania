#include "StandardCollisionSystem.h"
#include "../../GameObject.h"
#include "../../../Models/Factories/ObjectCollection.h"

using namespace Castlevania;

StandardCollisionSystem::StandardCollisionSystem(GameObject &parent) : parent{ parent }
{
}

IGameObject &StandardCollisionSystem::GetParent()
{
	return parent;
}

void StandardCollisionSystem::Update(ObjectCollection &objectCollection)
{
	auto &body = parent.GetBody();
	body.ClearCollisionData();

	if (!body.Enabled())
		return;

	auto results = std::vector<CollisionResult>{};
	auto &boundaries = objectCollection.boundaries;
	auto &entities = objectCollection.entities;

	for (auto &boundary : boundaries)
	{
		CalculateCollision(*boundary, results);
	}

	for (auto &entity : entities)
	{
		CalculateCollision(*entity, results);
	}

	// TODO: do we need to sort?
	body.SetCollisionData(FilterCollision(results));
}
