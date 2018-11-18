#include "PlayerResponseSystem.h"

using namespace Castlevania;

PlayerResponseSystem::PlayerResponseSystem(Player &parent) : parent{ parent }
{
}

void PlayerResponseSystem::Update()
{
	auto distance = parent.GetDistance();
	auto collisionData = parent.GetBody().GetCollisionData();

	parent.isOnGround = false;

	if (collisionData.collisionResults.size() == 0)
	{
		parent.Move(distance);
		return;
	}

	for (auto result : collisionData.collisionResults)
	{
		auto type = (EntityType)result.collidedObject.GetType();

		switch (type)
		{
			case EntityType::Boundary:
				auto normal = collisionData.minNormal;
				auto time = collisionData.minTime;

				// *0.4f : need to push out a bit to avoid overlapping next frame
				distance = distance * time + normal * 0.4f;
				parent.Move(distance);

				if (result.direction == Direction::Top) // Touch ground
				{
					parent.isOnGround = true;

					if (parent.GetMoveState() == MoveState::FALLING
						|| parent.GetMoveState() == MoveState::LANDING
						|| parent.GetMoveState() == MoveState::FALLING_HARD)
					{
						parent.Land();
					}
				}
				else if (result.direction == Direction::Right || result.direction == Direction::Left)
				{
					parent.SetVelocity_X(0);
				}
				else // (result.direction == Direction::Bottom)
				{
					parent.SetVelocity_Y(0);
				}
				break;
		}
	}
}
