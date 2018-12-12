#include "PlayerResponseSystem.h"
#include "NearbyObjects.h"
#include "../../Settings.h"
#include "../../UpdateData.h"
#include "../../../Scenes/Stages/StageEvent.h"

using namespace Castlevania;

struct PlayerResponseSystem::ResponseResult
{
	bool isOnGround;
	NearbyObjects nearbyObjects;
};

PlayerResponseSystem::PlayerResponseSystem(Player &parent, ObjectFactory &objectFactory) :
	parent{ parent },
	objectFactory{ objectFactory }
{
}

GameObject &PlayerResponseSystem::GetParent()
{
	return parent;
}

void PlayerResponseSystem::Update(UpdateData &updateData)
{
	auto &objectCollection = *updateData.objectCollection;
	auto collisionData = parent.GetBody().GetCollisionData();
	auto responseResult = ResponseResult{};

	for (auto result : collisionData.collisionResults)
	{
		auto type = (EntityType)result.collidedObject.GetType();
		auto &collidedObject = result.collidedObject;

		switch (type)
		{
			case EntityType::Boundary:
				OnCollideWithBoundary(result, responseResult);
				break;

			case EntityType::Trigger:
				OnCollideWithTrigger(result, responseResult);
				break;

			case EntityType::Zombie:
			case EntityType::Panther:
			case EntityType::Fishman:
				OnCollideWithEnemy(result);
				break;

			case EntityType::VampireBat:
				OnCollideWithVampireBat(result);
				break;

			case EntityType::Fireball:
				OnCollideWithFireball(result);
				break;

			case EntityType::LargeHeart:
				OnCollideWithHeart(result);
				break;

			case EntityType::SmallHeart:
				OnCollideWithSmallHeart(result);
				break;

			case EntityType::WhipPowerup:
				OnCollideWithWhipPowerup(result);
				break;

			case EntityType::DaggerItem:
				OnCollideWithDaggerItem(result, objectCollection);
				break;

			case EntityType::Door:
				OnCollideWithDoor(result, responseResult);
				break;
		}
	}

	PostProcess(responseResult);
}

void PlayerResponseSystem::PostProcess(ResponseResult responseResult)
{
	if (wasOnGround != responseResult.isOnGround)
	{
		if (wasOnGround)
			OnFalling();
		
		wasOnGround = responseResult.isOnGround;
	}

	parent.nearbyObjects = responseResult.nearbyObjects;
}

Direction PlayerResponseSystem::GetPlayerHitDirection(GameObject &object, Direction direction)
{
	auto hitDirection = Direction{};

	switch (direction)
	{
		case Direction::Left:
		case Direction::Right:
			hitDirection = Opposite(direction);
			break;

		case Direction::Top:
		case Direction::Bottom:
			if (parent.GetOriginPosition().x <= object.GetOriginPosition().x)
				hitDirection = Direction::Left;
			else
				hitDirection = Direction::Right;
			break;
	}

	return hitDirection;
}

void PlayerResponseSystem::OnFalling()
{
	auto moveState = parent.GetMoveState();

	if (moveState == MoveState::WALKING
		|| moveState == MoveState::IDLE)
		parent.moveState = MoveState::FALLING_HARD;
}

void PlayerResponseSystem::OnCollideWithBoundary(CollisionResult &result, ResponseResult &responseResult)
{
	auto distance = parent.GetDistance();
	auto collisionData = parent.GetBody().GetCollisionData();

	switch (result.direction)
	{
		case Direction::Top: // Touch ground
			responseResult.isOnGround = true;

			// We dont care if there are obstacles (such as cornered wall
			// near the stair entry). Just move the player to the damn stair
			if (parent.IsOnStairs())
				break;

			switch (parent.GetMoveState())
			{
				case MoveState::FALLING:
				case MoveState::LANDING:
				case MoveState::FALLING_HARD:
					ClampDistance_Y(collisionData);
					parent.Land();
					break;

				case MoveState::TAKING_DAMAGE:
					if (parent.velocity.y > 0)
					{
						ClampDistance_Y(collisionData);
						parent.Land();
					}
					break;

				default:
					ClampDistance_Y(collisionData);
					break;
			}
			break;

		case Direction::Left:
		case Direction::Right:
			if (parent.IsOnStairs())
				break;

			ClampDistance_X(collisionData);
			parent.SetVelocity_X(0);
			break;
	}
}

void PlayerResponseSystem::OnCollideWithTrigger(CollisionResult &result, ResponseResult &responseResult)
{
	auto &trigger = dynamic_cast<Trigger&>(result.collidedObject);
	
	switch (trigger.GetTriggerType())
	{
		case TriggerType::STAIR_UP:
			responseResult.nearbyObjects.stair = &trigger;
			responseResult.nearbyObjects.stairHitDirection = result.direction;
			OnCollideWithStairUpTrigger(trigger);
			break;

		case TriggerType::STAIR_DOWN:
			responseResult.nearbyObjects.stair = &trigger;
			responseResult.nearbyObjects.stairHitDirection = result.direction;
			OnCollideWithStairDownTrigger(trigger);
			break;

		case TriggerType::NEXT_MAP:
			OnCollideWithNextMapTrigger(trigger);
			break;

		case TriggerType::CASTLE_ENTRANCE:
			OnCollideWithCastleEntranceTrigger(trigger);
			break;
	}
}

void PlayerResponseSystem::OnCollideWithEnemy(CollisionResult &result)
{
	auto &object = dynamic_cast<Enemy&>(result.collidedObject);
	auto hitDirection = GetPlayerHitDirection(object, result.direction);

	parent.TakeDamage(object.GetAttack(), hitDirection);
}

void PlayerResponseSystem::OnCollideWithVampireBat(CollisionResult &result)
{
	OnCollideWithEnemy(result);

	auto &vampireBat = dynamic_cast<VampireBat&>(result.collidedObject);

	vampireBat.Die();
}

void PlayerResponseSystem::OnCollideWithFireball(CollisionResult &result)
{
	auto &object = dynamic_cast<Fireball&>(result.collidedObject);
	auto hitDirection = GetPlayerHitDirection(object, result.direction);

	parent.TakeDamage(object.GetAttack(), hitDirection);
}

void PlayerResponseSystem::OnCollideWithHeart(CollisionResult &result)
{
	auto &largeHeart = dynamic_cast<GameObject&>(result.collidedObject);

	parent.data.hearts += 5;
	largeHeart.Destroy();
}

void PlayerResponseSystem::OnCollideWithSmallHeart(CollisionResult &result)
{
	auto &smallHeart = dynamic_cast<GameObject&>(result.collidedObject);

	parent.data.hearts += 1;
	smallHeart.Destroy();
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

void PlayerResponseSystem::OnCollideWithDaggerItem(CollisionResult &result, ObjectCollection &objectCollection)
{
	auto &daggerItem = dynamic_cast<GameObject&>(result.collidedObject);
	auto itemType = (EntityType)daggerItem.GetType();
	
	daggerItem.Destroy();
	parent.SetSubWeapon(itemType);
}

void PlayerResponseSystem::OnCollideWithDoor(CollisionResult &result, ResponseResult &responseResult)
{
	auto &door = dynamic_cast<Door&>(result.collidedObject);

	responseResult.nearbyObjects.door = &door;
	responseResult.nearbyObjects.doorHitDirection = result.direction;

	if (parent.GetMoveState() == MoveState::IDLE || parent.GetMoveState() == MoveState::WALKING)
	{
		parent.Idle();
		parent.Notify(NEXT_ROOM_CUTSCENE_STARTED);
		door.GetBody().Enabled(false);
	}
}

void PlayerResponseSystem::OnCollideWithStairUpTrigger(Trigger &trigger)
{
	if (parent.moveState == MoveState::GOING_DOWNSTAIRS || parent.moveState == MoveState::IDLE_DOWNSTAIRS)
	{
		auto triggerBbox = trigger.GetBoundingBox();
		auto parentBbox = parent.GetBoundingBox();
		auto parentFrame = parent.GetFrameRect();

		// -2: change to idle state when barely hit the floor to make the transition smoother
		if (parentBbox.bottom >= triggerBbox.bottom - 2)
		{
			parent.IdleOnGround();

			auto offsetBottom = parentFrame.bottom - parent.GetBoundingBox().bottom;
			// *0.4f : the magic number which make the object pushed out a bit to avoid overlapping next frame
			parent.position.y = triggerBbox.bottom - parentFrame.Height() + offsetBottom - 0.4f;
			parent.SetDistance_Y(0);
		}
	}
}

void PlayerResponseSystem::OnCollideWithStairDownTrigger(Trigger &trigger)
{
	if (parent.moveState == MoveState::GOING_UPSTAIRS || parent.moveState == MoveState::IDLE_UPSTAIRS)
	{
		auto triggerBbox = trigger.GetBoundingBox();
		auto parentBbox = parent.GetBoundingBox();
		auto parentFrame = parent.GetFrameRect();

		if (parentBbox.bottom <= triggerBbox.bottom)
		{
			parent.IdleOnGround();

			auto offsetBottom = parentFrame.bottom - parent.GetBoundingBox().bottom;
			parent.position.y = triggerBbox.bottom - parentFrame.Height() + offsetBottom - 0.4f;
			parent.SetDistance_Y(0);
		}
	}
}

void PlayerResponseSystem::OnCollideWithNextMapTrigger(Trigger &trigger)
{
	if (trigger.Enabled())
	{
		parent.Notify(NEXT_MAP_CUTSCENE_STARTED);
		trigger.Enabled(false);
	}
}

void PlayerResponseSystem::OnCollideWithCastleEntranceTrigger(Trigger &trigger)
{
	if (trigger.Enabled())
	{
		parent.Notify(GO_TO_CASTLE_CUTSCENE_STARTED);
		trigger.Enabled(false);
	}
}
