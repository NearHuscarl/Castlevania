#include "PantherCollisionSystem.h"
#include "Panther.h"
#include "../../UpdateData.h"
#include "../../Settings.h"

using namespace Castlevania;

PantherCollisionSystem::PantherCollisionSystem(Panther &parent) : parent{ parent }
{
}

IGameObject &PantherCollisionSystem::GetParent()
{
	return parent;
}

void PantherCollisionSystem::Update(UpdateData &updateData)
{
	auto &body = parent.GetBody();
	body.ClearCollisionData();

	if (!body.Enabled())
		return;

	auto results = std::vector<CollisionResult>{};
	auto &collisionObject = *updateData.collisionObjects;

	for (auto staticObject : collisionObject)
	{
		CalculateCollision(*staticObject, results);
	}

	// TODO: do we need to sort?
	body.SetCollisionData(FilterCollisionResults(results));

	// Check if player is inside active zone
	if (!parent.IsActive())
	{
		auto player = updateData.player;
		auto activeZone = parent.GetActiveZone();

		// note to myself: do not use swept AABB algorithm for collision detection in this case.
		// It wont work properly when calculating collision between a static object (in this
		// scenario the one that check collision - ActiveArea) and a dynamic object (Player)
		// The reason is because since only the distance of the Player is taken into account
		// and the fact that it is actually from the last time the game loop ran (Player has already
		// moved that distance), it may lead to potential out-of-sync behaviour. 
		//auto result = player->GetBody().PredictCollision(activeZone);

		//if (result.ShouldCollide())
		//{
		//	parent.SendMessageToSystems(PLAYER_IN_RANGE);
		//}

		if (activeZone.TouchesOrIntersects(player->GetBoundingBox()))
		{
			parent.SendMessageToSystems(PLAYER_IN_RANGE);
		}
	}
}
