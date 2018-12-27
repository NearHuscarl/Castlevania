#include "WeaponCollisionSystem.h"
#include "../UpdateData.h"

using namespace Castlevania;

WeaponCollisionSystem::WeaponCollisionSystem(GameObject &parent) : parent{ parent }
{
}

void WeaponCollisionSystem::Update(UpdateData &updateData)
{
	auto &body = parent.GetBody();
	body.ClearCollisionData();

	if (!body.Enabled())
		return;

	auto results = std::vector<CollisionResult>{};
	auto collisionObjects = *updateData.collisionObjects;

	for (auto &collisionObject : collisionObjects)
	{
		if (!collisionObject->GetBody().Enabled())
			continue;

		auto entityRect = collisionObject->GetFrameRect();

		if (parent.GetBoundingBox().TouchesOrIntersects(entityRect))
		{
			results.push_back(CollisionResult{ 0, Direction::None, *collisionObject });
		}
	}

	body.SetCollisionData(CollisionData{ results });
}
