#include "StaticResponseSystem.h"
#include "../../GameObject.h"
#include "../../Settings.h"

using namespace Castlevania;

StaticResponseSystem::StaticResponseSystem(GameObject &parent) : parent{ parent }
{
	wasOnGround = false;
}

void StaticResponseSystem::Update(ObjectCollection &objectCollection)
{
	auto collisionData = parent.GetBody().GetCollisionData();
	auto isOnGround = false;

	for (auto result : collisionData.collisionResults)
	{
		auto type = (EntityType)result.collidedObject.GetType();

		switch (type)
		{
			case EntityType::Boundary:
			{
				auto distance = parent.GetDistance();
				auto time = collisionData.minTime;
				auto normal = collisionData.minNormal;

				// *0.4f : need to push out a bit to avoid overlapping next frame
				distance = distance * time + normal * 0.4f;
				parent.SetDistance(distance);

				if (result.direction == Direction::Top)
					isOnGround = true;
				break;
			}
		}
	}

	if (wasOnGround != isOnGround)
	{
		if (wasOnGround)
			parent.SendMessageToSystems(START_FALLING);
		else
			parent.SendMessageToSystems(START_LANDING);

		wasOnGround = isOnGround;
	}
}
