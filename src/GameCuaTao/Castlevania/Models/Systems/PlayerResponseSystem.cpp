#include "PlayerResponseSystem.h"

using namespace Castlevania;

PlayerResponseSystem::PlayerResponseSystem(Player &parent) : parent{ parent }
{
}

void PlayerResponseSystem::Update(CollisionData collisionData)
{
	auto distance = parent.GetDistance();

	if (collisionData.collisionResults.size() == 0)
	{
		parent.Move(distance);
		return;
	}

	//auto normal = collisionData.minNormal;
	//auto time = collisionData.minTime;

	//// *0.4f : need to push out a bit to avoid overlapping next frame
	//distance = distance * time + normal * 0.4f;

	//auto velocity = parent.GetVelocity();

	//if (normal.x != 0)
	//	velocity.x = 0;
	//if (normal.y != 0)
	//	velocity.y = 0;

	//parent.Move(distance);
	//parent.SetVelocity(velocity);

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
					parent.SetVelocity_Y(0);

					if (parent.GetMoveState() == MoveState::JUMPING)
						parent.Idle();

					if (parent.GetAttackState() == AttackState::ATTACKING)
						parent.SetVelocity_X(0); // Still keep attacking on the ground but not moving anymore
				}
				else if (result.direction == Direction::Right || result.direction == Direction::Left)
				{
					parent.SetVelocity_X(0);
				}
				else // result.direction == Direction::Bottom
				{
					parent.SetVelocity_Y(0);
				}
				break;
		}
	}
}
