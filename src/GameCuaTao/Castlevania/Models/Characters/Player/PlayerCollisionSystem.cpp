#include "PlayerCollisionSystem.h"
#include "../../GameObject.h"
#include "../../../Models/UpdateData.h"

using namespace Castlevania;

PlayerCollisionSystem::PlayerCollisionSystem(GameObject &parent) : parent{ parent }
{
}

IGameObject &PlayerCollisionSystem::GetParent()
{
	return parent;
}

void PlayerCollisionSystem::Update(UpdateData &updateData)
{
	auto &body = parent.GetBody();
	body.ClearCollisionData();

	if (!body.Enabled())
		return;

	auto results = std::vector<CollisionResult>{};
	auto collisionObjects = *updateData.collisionObjects;
	auto otherObjects = updateData.objects;

	for (auto &collisionObject : collisionObjects)
	{
		CalculateCollision(*collisionObject, results);
	}

	for (auto &object : otherObjects->staticObjects)
	{
		if (object->GetId() == ObjectId::BossFightArea) // We know we only need to check that one object in the whole collection
			CalculateCollision(*object, results);
	}

	// TODO: do we need to sort?
	body.SetCollisionData(FilterCollisionResults(results));
}
