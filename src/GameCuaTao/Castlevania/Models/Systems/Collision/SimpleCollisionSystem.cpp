#include "SimpleCollisionSystem.h"
#include "../../GameObject.h"
#include "../../../Factories/ObjectCollection.h"

using namespace Castlevania;

SimpleCollisionSystem::SimpleCollisionSystem(GameObject &parent) : parent{ parent }
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

	auto results = CollisionResults{};
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

	auto collisionData = CollisionData{ results };

	body.SetCollisionData(collisionData);
}

void SimpleCollisionSystem::CalculateCollision(GameObject &gameObject, CollisionResults &results)
{
	auto body = gameObject.GetBody();

	if (!body.Enabled())
		return;

	auto objectBoundingBox = gameObject.GetBoundingBox();

	if (parent.GetBoundingBox().TouchesOrIntersects(objectBoundingBox))
	{
		results.push_back(CollisionResult{ 0, Direction::None, gameObject });
	}
}
