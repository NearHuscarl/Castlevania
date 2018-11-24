#include "WhipResponseSystem.h"
#include "../../Models/Factories/ObjectCollection.h"
#include "../Items/FirePit.h"

using namespace Castlevania;

WhipResponseSystem::WhipResponseSystem(Whip &parent) : parent{ parent }
{
}

void WhipResponseSystem::Update(ObjectCollection &objectCollection)
{
	auto collisionData = parent.GetBody().GetCollisionData();

	if (collisionData.collisionResults.size() == 0)
		return;

	for (auto result : collisionData.collisionResults)
	{
		auto type = (EntityType)result.collidedObject.GetType();

		switch (type)
		{
			case EntityType::FirePit:
				OnCollideWithFirePit(result, objectCollection);
				break;
		}
	}
}

void WhipResponseSystem::OnCollideWithFirePit(CollisionResult &result, ObjectCollection &objectCollection)
{
	auto &firePit = dynamic_cast<FirePit&>(result.collidedObject);

	firePit.OnBeingHit();
}
