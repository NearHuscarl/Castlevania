#include "StandardCollisionSystem.h"
#include "../../GameObject.h"
#include "../../../Models/UpdateData.h"

using namespace Castlevania;

StandardCollisionSystem::StandardCollisionSystem(GameObject &parent) : parent{ parent }
{
}

IGameObject &StandardCollisionSystem::GetParent()
{
	return parent;
}

void StandardCollisionSystem::Update(UpdateData &updateData)
{
	auto &body = parent.GetBody();
	body.ClearCollisionData();

	if (!body.Enabled())
		return;

	auto results = std::vector<CollisionResult>{};
	auto &objectCollection = *updateData.objectCollection;
	auto &staticObjects = objectCollection.staticObjects;
	auto &entities = objectCollection.entities;

	for (auto &staticObject : staticObjects)
	{
		CalculateCollision(*staticObject, results);
	}

	for (auto &entity : entities)
	{
		CalculateCollision(*entity, results);
	}

	// TODO: do we need to sort?
	body.SetCollisionData(FilterCollision(results));
}
