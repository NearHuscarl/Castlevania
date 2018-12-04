#include "GroundResponseSystem.h"
#include "../../GameObject.h"
#include "../../Settings.h"

using namespace Castlevania;

GroundResponseSystem::GroundResponseSystem(GameObject &parent) : parent{ parent }
{
	wasOnGround = false;
}

void GroundResponseSystem::Update(ObjectCollection &objectCollection)
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
				if (result.direction != Direction::Top)
					break;

				auto distance = parent.GetDistance();
				auto time = collisionData.minTime;
				auto normal = collisionData.minNormal;

				// *0.4f : need to push out a bit to avoid overlapping next frame
				distance = distance * time + normal * 0.4f;
				parent.SetDistance(distance);

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
