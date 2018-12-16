#include "PantherCollisionSystem.h"
#include "Panther.h"
#include "../../Factories/ObjectCollection.h"
#include "../../Settings.h"

using namespace Castlevania;

PantherCollisionSystem::PantherCollisionSystem(Panther &parent) : parent{ parent }
{
}

IGameObject &PantherCollisionSystem::GetParent()
{
	return parent;
}

void PantherCollisionSystem::Update(ObjectCollection &objectCollection)
{
	auto &body = parent.GetBody();
	body.ClearCollisionData();

	if (!body.Enabled())
		return;

	auto results = std::vector<CollisionResult>{};
	auto &boundaries = objectCollection.boundaries;

	for (auto &boundary : boundaries)
	{
		CalculateCollision(*boundary, results);
	}

	// TODO: do we need to sort?
	body.SetCollisionData(FilterCollision(results));

	// Check if player is inside active zone
	if (!parent.IsActive())
	{
		auto player = objectCollection.player;
		auto activeArea = parent.GetActiveArea();

		// note to myself: do not use swept AABB algorithm for collision detection in this case.
		// It wont work properly when calculating collision between a static object (in this
		// scenario the one that check collision - ActiveArea) and a dynamic object (Player)
		// The reason is because since only the distance of the Player is taken into account
		// and the fact that it is actually from the last time the game loop ran (Player has already
		// moved that distance), it may lead to potential out-of-sync behaviour. 
		//auto result = player->GetBody().PredictCollision(activeArea);

		//if (result.ShouldCollide())
		//{
		//	parent.SendMessageToSystems(PLAYER_IN_RANGE);
		//}

		if (activeArea.TouchesOrIntersects(player->GetBoundingBox()))
		{
			parent.SendMessageToSystems(PLAYER_IN_RANGE);
		}
	}
}
