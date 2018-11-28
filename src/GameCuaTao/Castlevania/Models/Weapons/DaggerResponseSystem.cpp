#include "DaggerResponseSystem.h"
#include "../../Models/Factories/ObjectCollection.h"
#include "../Items/Brazier.h"

using namespace Castlevania;

DaggerResponseSystem::DaggerResponseSystem(GameObject &parent) : parent{ parent }
{
}

void DaggerResponseSystem::Update(ObjectCollection &objectCollection)
{
	auto collisionData = parent.GetBody().GetCollisionData();

	if (collisionData.collisionResults.size() == 0)
		return;

	for (auto result : collisionData.collisionResults)
	{
		auto type = (EntityType)result.collidedObject.GetType();

		switch (type)
		{
			case EntityType::Brazier:
				OnCollideWithBrazier(result, objectCollection);
				break;
		}
	}
}

void DaggerResponseSystem::OnCollideWithBrazier(CollisionResult &result, ObjectCollection &objectCollection)
{
	auto &brazier = dynamic_cast<Brazier&>(result.collidedObject);
	auto item = brazier.SpawnItem();

	item->SetOriginPosition(brazier.GetOriginPosition());
	brazier.Destroy();

	objectCollection.entities.push_back(std::move(item));
}
