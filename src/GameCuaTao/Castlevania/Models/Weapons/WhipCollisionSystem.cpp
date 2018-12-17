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
	auto &entities = updateData.objectCollection->entities;

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
