#include "KnifeResponseSystem.h"
#include "../../Factories/ObjectCollection.h"
#include "../Items/FirePit.h"

using namespace Castlevania;

KnifeResponseSystem::KnifeResponseSystem(GameObject &parent) : parent{ parent }
{
}

void KnifeResponseSystem::Update(ObjectCollection &objectCollection)
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

void KnifeResponseSystem::OnCollideWithFirePit(CollisionResult &result, ObjectCollection &objectCollection)
{
	auto &firePit = dynamic_cast<FirePit&>(result.collidedObject);
	auto item = firePit.SpawnItem();

	item->SetOriginPosition(firePit.GetOriginPosition());
	firePit.Destroy();

	objectCollection.entities.push_back(std::move(item));
}
