#include "Direct2DGame/MathHelper.h"
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
	auto &objectCollection = *updateData.objectCollection;

	for (auto &boundary : objectCollection.boundaries)
	{
		CalculateCollision(*boundary, results);
	}

	for (auto &trigger : objectCollection.triggers)
	{
		CalculateCollision(*trigger, results);
	}

	for (auto &entity : objectCollection.entities)
	{
		CalculateCollision(*entity, results);
	}

	for (auto &area : objectCollection.areas)
	{
		CalculateCollision(*area, results);
	}

	// TODO: do we need to sort?
	body.SetCollisionData(FilterCollision(results));
}
