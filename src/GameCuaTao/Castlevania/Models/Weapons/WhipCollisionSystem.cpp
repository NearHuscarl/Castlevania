#include "WhipCollisionSystem.h"
#include "../UpdateData.h"

using namespace Castlevania;

WhipCollisionSystem::WhipCollisionSystem(GameObject &parent) : parent{ parent }
{
}

void WhipCollisionSystem::Update(UpdateData &updateData)
{
	auto &body = parent.GetBody();
	body.ClearCollisionData();

	if (!body.Enabled())
		return;

	auto results = std::vector<CollisionResult>{};
	auto collisionObjects = *updateData.collisionObjects;

	for (auto &collisionObject : collisionObjects)
	{
		auto entityRect = collisionObject->GetFrameRect();

		if (parent.GetBoundingBox().TouchesOrIntersects(entityRect))
		{
			results.push_back(CollisionResult{ 0, Direction::None, *collisionObject });
		}
	}

	body.SetCollisionData(CollisionData{ results });
}
