#include "SimpleCollisionSystem.h"
#include "../../GameObject.h"
#include "../../../Models/UpdateData.h"

using namespace Castlevania;

SimpleCollisionSystem::SimpleCollisionSystem(GameObject &parent) : parent{ parent }
{
}

IGameObject &SimpleCollisionSystem::GetParent()
{
	return parent;
}

void SimpleCollisionSystem::Update(UpdateData &updateData)
{
	auto &body = parent.GetBody();
	body.ClearCollisionData();

	if (!body.Enabled())
		return;

	auto results = std::vector<CollisionResult>{};
	auto collisionObjects = *updateData.collisionObjects;

	for (auto &collisionObject : collisionObjects)
	{
		CalculateStaticCollision(*collisionObject, results);
	}

	body.SetCollisionData(CollisionData{ results });
}
