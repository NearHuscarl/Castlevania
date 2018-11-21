#include "StandardCollisionSystem.h"
#include "../../GameObject.h"
#include "../../../Factories/ObjectCollection.h"

using namespace Castlevania;

StandardCollisionSystem::StandardCollisionSystem(GameObject &parent) : CollisionSystem{ parent }
{
}

void StandardCollisionSystem::Update(ObjectCollection &objectCollection)
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
		CalculateCollision(*boundary, results);
	}

	for (auto &entity : entities)
	{
		CalculateCollision(*entity, results);
	}

	// TODO: do we need to sort?
	body.SetCollisionData(FilterCollision(results));
}
