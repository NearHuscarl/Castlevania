#include "WhipResponseSystem.h"
#include "../../Factories/ObjectCollection.h"
#include "../Items/FirePit.h"
#include "../Items/Heart.h"

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
				auto &object = dynamic_cast<FirePit&>(result.collidedObject);
				auto item = object.SpawnItem();

				item->SetPosition(object.GetPosition());

				//objectCollection.entities.push_back(item);
				break;
		}
	}
}
