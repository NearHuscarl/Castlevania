#include "CollisionSystem.h"
#include "../../IGameObject.h"
#include "../../../Models/Factories/ObjectCollection.h"

using namespace Castlevania;

CollisionSystem::CollisionSystem(IGameObject &parent) : parent{ parent }
{
}

void CollisionSystem::CalculateCollision(IGameObject &gameObject, CollisionResults &results)
{
	if (!gameObject.GetBody().Enabled())
		return;

	auto result = CalculateStaticCollision(gameObject, results);

	if (!result) // First method failed, fallback to use Swept AABB algo check
	{
		CalculateDynamicCollision(gameObject, results);
	}
}

bool CollisionSystem::CalculateStaticCollision(IGameObject &gameObject, CollisionResults &results)
{
	auto objectBoundingBox = gameObject.GetBoundingBox();

	if (parent.GetBoundingBox().TouchesOrIntersects(objectBoundingBox))
	{
		results.push_back(CollisionResult{ 0, Direction::None, gameObject });
		return true;
	}

	return false;
}

bool CollisionSystem::CalculateDynamicCollision(IGameObject &gameObject, CollisionResults &results)
{
	auto result = parent.GetBody().PredictCollision(gameObject);

	if (result.ShouldCollide())
	{
		results.push_back(result);
		return true;
	}

	return false;
}

// Get a list of objects that has the shortest time to collide with or already collided
CollisionData CollisionSystem::FilterCollision(CollisionResults collisionResults)
{
	if (collisionResults.size() == 0)
		return CollisionData{};

	auto minNormal = Vector2::Zero();
	auto minTime = Vector2::One();

	auto minIndex_x = -1;
	auto minIndex_y = -1;
	auto collidedIndexes = std::vector<int>{}; // index of collision results already collide with parent

	for (unsigned int i = 0; i < collisionResults.size(); i++)
	{
		auto result = collisionResults[i];

		if (result.direction == Direction::Left || result.direction == Direction::Right)
		{
			if (result.timeToCollide < minTime.x)
			{
				minTime.x = result.timeToCollide;
				minNormal.x = result.direction == Direction::Left ? -1.0f : 1.0f;
				minIndex_x = i;
			}
		}

		if (result.direction == Direction::Top || result.direction == Direction::Bottom)
		{
			if (result.timeToCollide < minTime.y)
			{
				minTime.y = result.timeToCollide;
				minNormal.y = result.direction == Direction::Top ? -1.0f : 1.0f;
				minIndex_y = i;
			}
		}

		if (result.direction == Direction::None && result.timeToCollide == 0) // Already collide
		{
			collidedIndexes.push_back(i);
		}
	}

	auto filteredCollisionResults = CollisionResults{};

	if (minIndex_x >= 0)
		filteredCollisionResults.push_back(collisionResults[minIndex_x]);

	if (minIndex_y >= 0)
		filteredCollisionResults.push_back(collisionResults[minIndex_y]);

	for (auto index : collidedIndexes)
		filteredCollisionResults.push_back(collisionResults[index]);

	return CollisionData{ filteredCollisionResults, minTime, minNormal };
}