#include "PlayerResponseSystem.h"

using namespace Castlevania;

PlayerResponseSystem::PlayerResponseSystem(Player &parent) : parent{ parent }
{
}

void PlayerResponseSystem::Update(ObjectCollection &objectCollection)
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
				if (result.direction == Direction::Top) // Touch ground
				{
					ClampDistance_Y(collisionData, distance);

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
					ClampDistance_X(collisionData, distance);
					parent.SetVelocity_X(0);
				}
				else // (result.direction == Direction::Bottom)
				{
					ClampDistance_Y(collisionData, distance);
					parent.SetVelocity_Y(0);
				}
				break;
		}
	}

	parent.Move(distance);
}

void PlayerResponseSystem::ClampDistance_X(CollisionData collisionData, Vector2 &distance)
{
	auto time = collisionData.minTime;
	auto normal = collisionData.minNormal;

	// *0.4f : need to push out a bit to avoid overlapping next frame
	distance.x = distance.x * time.x + normal.x * 0.4f;
}

void PlayerResponseSystem::ClampDistance_Y(CollisionData collisionData, Vector2 &distance)
{
	auto time = collisionData.minTime;
	auto normal = collisionData.minNormal;

	distance.y = distance.y * time.y + normal.y * 0.4f;
}