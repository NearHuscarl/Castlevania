#include "Direct2DGame/MathHelper.h"
#include "CollisionSystem.h"
#include "../GameObject.h"
#include "../../Factories/ObjectCollection.h"

using namespace Castlevania;

CollisionSystem::CollisionSystem(GameObject &parent) : parent{ parent }
{
}

CollisionData CollisionSystem::GetCollisionData()
{
	return collisionData;
}

void CollisionSystem::Update(ObjectCollection &objectCollection)
{
	auto results = std::vector<CollisionResult>{};

	auto &boundaries = objectCollection.boundaries;

	for (auto &boundary : boundaries)
	{
		auto result = parent.GetBody().PredictCollision(*boundary.get());

		if (result.ShouldCollide())
			results.push_back(result);
	}

	// TODO: do we need to sort?
	collisionData = FilterCollision(results);
}

// Get the list of objects that has the shortest time to collide with
CollisionData CollisionSystem::FilterCollision(CollisionResults collisionResults)
{
	if (collisionResults.size() == 0)
		return CollisionData{};
	
	auto minNormal = Vector2::Zero();
	auto minTime = Vector2::One();

	auto minIndex_x = -1;
	auto minIndex_y = -1;

	for (auto i = 0; i < collisionResults.size(); i++)
	{
		auto result = collisionResults[i];

		if (result.direction == Direction::Left || result.direction == Direction::Right)
		{
			minTime.x = MathHelper::Min(minTime.x, result.timeToCollide);
			minNormal.x = result.direction == Direction::Left ? -1.0f : 1.0f;
			minIndex_x = i;
		}

		if (result.direction == Direction::Top || result.direction == Direction::Bottom)
		{
			minTime.y = MathHelper::Min(minTime.y, result.timeToCollide);
			minNormal.y = result.direction == Direction::Top ? -1.0f : 1.0f;
			minIndex_y = i;
		}
	}

	auto filteredCollisionResults = CollisionResults{};

	if (minIndex_x >= 0)
		filteredCollisionResults.push_back(collisionResults[minIndex_x]);
	if (minIndex_y >= 0)
		filteredCollisionResults.push_back(collisionResults[minIndex_y]);

	return CollisionData{ filteredCollisionResults, minTime, minNormal };
}
