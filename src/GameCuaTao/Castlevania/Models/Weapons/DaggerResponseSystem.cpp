#include "DaggerResponseSystem.h"
#include "../../Models/UpdateData.h"
#include "../Items/Container.h"

using namespace Castlevania;

DaggerResponseSystem::DaggerResponseSystem(GameObject &parent) : parent{ parent }
{
}

void DaggerResponseSystem::Update(UpdateData &updateData)
{
	auto &objectCollection = *updateData.objectCollection;
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
	auto &brazier = dynamic_cast<Container&>(result.collidedObject);

	brazier.OnBeingHit();
	parent.Destroy();
}
