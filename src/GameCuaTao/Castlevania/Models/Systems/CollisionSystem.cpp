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

void CollisionSystem::Update(float deltaTime, ObjectCollection &objectCollection)
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

void CollisionSystem::ResolveCollision(CollisionData collisionData, float deltaTime)
{
	auto normal = collisionData.minNormal;
	auto time = collisionData.minTime;

	auto position = parent.GetPosition();
	auto velocity = parent.GetVelocity();
	auto distance = velocity * deltaTime;

	// *0.4f : need to push out a bit to avoid overlapping next frame
	position.x += distance.x * time.x + normal.x * 0.4f;
	position.y += distance.y * time.y + normal.y * 0.4f;

	if (normal.x != 0)
		velocity.x = 0;
	if (normal.y != 0)
		velocity.y = 0;

	parent.SetPosition(position);
	parent.SetVelocity(velocity);
}

// Get the list of objects that has the shortest time to collide with
CollisionData CollisionSystem::FilterCollision(CollisionResults collisionResults)
{
	if (collisionResults.size() == 0)
	{
		return CollisionData{};
	}
	
	auto minNormal = Vector2::Zero();
	auto minTime = Vector2::One();

	auto minIndex_x = -1;
	auto minIndex_y = -1;

	for (auto i = 0; i < collisionResults.size(); i++)
	{
		if (collisionResults[i].direction == Direction::Left &&
			collisionResults[i].direction == Direction::Right)
		{
			minTime.x = MathHelper::Min(minTime.x, collisionResults[i].timeToCollide);
			minIndex_x = i;
		}

		if (collisionResults[i].direction == Direction::Top &&
			collisionResults[i].direction == Direction::Bottom)
		{
			minTime.y = MathHelper::Min(minTime.y, collisionResults[i].timeToCollide);
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
