#include "WhipCollisionSystem.h"
#include "../Factories/ObjectCollection.h"

using namespace Castlevania;

WhipCollisionSystem::WhipCollisionSystem(GameObject &parent) : parent{ parent }
{
}

void WhipCollisionSystem::Update(ObjectCollection &objectCollection)
{
	auto &body = parent.GetBody();

	if (!body.Enabled())
	{
		body.ClearCollisionData();
		return;
	}

	auto results = std::vector<CollisionResult>{};
	auto &entities = objectCollection.entities;

	for (auto &entity : entities)
	{
		auto entityRect = entity->GetFrameRect();

		if (parent.GetBoundingBox().TouchesOrIntersects(entityRect))
		{
			results.push_back(CollisionResult{ 0, Direction::None, *entity });
		}
	}

	body.SetCollisionData(CollisionData{ results });
}
