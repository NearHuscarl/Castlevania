#include "StaticResponseSystem.h"
#include "../../GameObject.h"

using namespace Castlevania;

StaticResponseSystem::StaticResponseSystem(GameObject &parent) : parent{ parent }
{
}

void StaticResponseSystem::Update(ObjectCollection &objectCollection)
{
	auto collisionData = parent.GetBody().GetCollisionData();

	if (collisionData.collisionResults.size() == 0)
	{
		return;
	}

	for (auto result : collisionData.collisionResults)
	{
		auto type = (EntityType)result.collidedObject.GetType();

		switch (type)
		{
			case EntityType::Boundary:
				auto distance = parent.GetDistance();
				auto time = collisionData.minTime;
				auto normal = collisionData.minNormal;

				// *0.4f : need to push out a bit to avoid overlapping next frame
				distance = distance * time + normal * 0.4f;
				parent.SetDistance(distance);

				auto velocity = parent.GetVelocity();

				if (normal.x != 0)
					velocity.x = 0;
				if (normal.y != 0)
					velocity.y = 0;

				parent.SetVelocity(velocity);
				break;
		}
	}
}
