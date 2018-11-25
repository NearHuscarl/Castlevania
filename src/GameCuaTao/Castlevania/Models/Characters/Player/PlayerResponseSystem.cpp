#include "PlayerResponseSystem.h"
#include "PlayerSettings.h"
#include "../../../Models/Factories/ObjectCollection.h"

using namespace Castlevania;

PlayerResponseSystem::PlayerResponseSystem(Player &parent, ObjectFactory &objectFactory) :
	parent{ parent },
	objectFactory{ objectFactory }
{
}

void PlayerResponseSystem::Update(ObjectCollection &objectCollection)
{
	auto collisionData = parent.GetBody().GetCollisionData();
	auto isOnGround = false;

	for (auto result : collisionData.collisionResults)
	{
		auto type = (EntityType)result.collidedObject.GetType();
		auto &collidedObject = result.collidedObject;

		switch (type)
		{
			case EntityType::Boundary:
				OnCollideWithBoundary(result, isOnGround);
				break;

			case EntityType::Heart:
				OnCollideWithHeart(result);
				break;

			case EntityType::WhipPowerup:
				OnCollideWithWhipPowerup(result);
				break;

			case EntityType::KnifeItem:
				OnCollideWithKnifeItem(result, objectCollection);
				break;
		}
	}

	SetIsOnGround(isOnGround);
}

void PlayerResponseSystem::SetIsOnGround(bool value)
{
	if (isOnGround != value && isOnGround)
	{
		parent.SendMessageToSystems(START_FALLING);
	}
	
	isOnGround = value;
}

void PlayerResponseSystem::ClampDistance_X(CollisionData collisionData)
{
	auto distance = parent.GetDistance();
	auto time = collisionData.minTime;
	auto normal = collisionData.minNormal;

	// *0.4f : need to push out a bit to avoid overlapping next frame
	distance.x = distance.x * time.x + normal.x * 0.4f;
	parent.SetDistance(distance);
}

void PlayerResponseSystem::ClampDistance_Y(CollisionData collisionData)
{
	auto distance = parent.GetDistance();
	auto time = collisionData.minTime;
	auto normal = collisionData.minNormal;

	distance.y = distance.y * time.y + normal.y * 0.4f;
	parent.SetDistance(distance);
}

void PlayerResponseSystem::OnCollideWithBoundary(CollisionResult &result, bool &isOnGround)
{
	auto distance = parent.GetDistance();
	auto collisionData = parent.GetBody().GetCollisionData();

	switch (result.direction)
	{
		case Direction::Top: // Touch ground
			ClampDistance_Y(collisionData);

			isOnGround = true;

			if (parent.GetMoveState() == MoveState::FALLING
				|| parent.GetMoveState() == MoveState::LANDING
				|| parent.GetMoveState() == MoveState::FALLING_HARD)
			{
				parent.Land();
			}
			break;

		case Direction::Left:
		case Direction::Right:
			ClampDistance_X(collisionData);
			parent.SetVelocity_X(0);
			break;

		case Direction::Bottom:
			ClampDistance_Y(collisionData);
			parent.SetVelocity_Y(0);
			break;
	}
}

void PlayerResponseSystem::OnCollideWithHeart(CollisionResult &result)
{
	auto &heart = dynamic_cast<GameObject&>(result.collidedObject);

	parent.data.hearts += 5;
	heart.Destroy();
}

void PlayerResponseSystem::OnCollideWithWhipPowerup(CollisionResult &result)
{
	// Only consume this powerup on the ground because I only have flashing sprites on ground
	if (parent.GetMoveState() != MoveState::IDLE
		&& parent.GetMoveState() != MoveState::WALKING)
		return;

	parent.Flash();

	auto &whipPowerup = dynamic_cast<GameObject&>(result.collidedObject);
	auto &whip = parent.whip;

	whip->Upgrade();

	if (whip->GetLevel() == WHIP_MAX_LEVEL)
	{
		whip = objectFactory.CreateFlashingWhip(parent);
		whip->SetFacing(parent.facing);
	}

	whipPowerup.Destroy();
}

void PlayerResponseSystem::OnCollideWithKnifeItem(CollisionResult &result, ObjectCollection &objectCollection)
{
	auto &knifeItem = dynamic_cast<GameObject&>(result.collidedObject);
	auto itemType = (EntityType)knifeItem.GetType();
	
	knifeItem.Destroy();
	parent.SetSecondaryWeapon(itemType);
}