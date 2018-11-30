#include "SimpleCollisionSystem.h"
#include "../../GameObject.h"
#include "../../../Models/Factories/ObjectCollection.h"

using namespace Castlevania;

SimpleCollisionSystem::SimpleCollisionSystem(GameObject &parent) : CollisionSystem{ parent }
{
}

void SimpleCollisionSystem::Update(ObjectCollection &objectCollection)
{
	auto &body = parent.GetBody();

	if (!body.Enabled())
	{
		body.ClearCollisionData();
		return;
	}

	auto results = std::vector<CollisionResult>{};
	auto &boundaries = objectCollection.boundaries;
	auto &entities = objectCollection.entities;

	for (auto &boundary : boundaries)
	{
		CalculateStaticCollision(*boundary, results);
	}

	for (auto &entity : entities)
	{
		CalculateStaticCollision(*entity, results);
	}

	// TODO: do we need to sort?
	body.SetCollisionData(FilterCollision(results));
}
