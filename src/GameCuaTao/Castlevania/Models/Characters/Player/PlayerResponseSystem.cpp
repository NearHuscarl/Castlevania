#include "PlayerResponseSystem.h"
#include "../../Settings.h"
#include "../../../Models/Factories/ObjectCollection.h"
#include "../../../Scenes/Stages/StageEvent.h"

using namespace Castlevania;

PlayerResponseSystem::PlayerResponseSystem(Player &parent, ObjectFactory &objectFactory) :
	parent{ parent },
	objectFactory{ objectFactory }
{
}

GameObject &PlayerResponseSystem::GetParent()
{
	return parent;
}

void PlayerResponseSystem::Update(ObjectCollection &objectCollection)
{
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
			case EntityType::VampireBat:
				OnCollideWithEnemy(result);
				break;

			case EntityType::LargeHeart:
				OnCollideWithHeart(result);
				break;

			case EntityType::WhipPowerup:
				OnCollideWithWhipPowerup(result);
				break;

			case EntityType::DaggerItem:
				OnCollideWithDaggerItem(result, objectCollection);
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

	parent.nearbyStair = responseResult.stairTrigger;
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
			OnCollideWithStairUpTrigger(trigger, responseResult);
			break;

		case TriggerType::STAIR_DOWN:
			OnCollideWithStairDownTrigger(trigger, responseResult);
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
	auto &enemy = dynamic_cast<Enemy&>(result.collidedObject);

	parent.TakeDamage(enemy.GetAttack(), Opposite(result.direction));
}

void PlayerResponseSystem::OnCollideWithHeart(CollisionResult &result)
{
	auto &largeHeart = dynamic_cast<GameObject&>(result.collidedObject);

	parent.data.hearts += 5;
	largeHeart.Destroy();
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

void PlayerResponseSystem::OnCollideWithStairUpTrigger(Trigger &trigger, ResponseResult &responseResult)
{
	responseResult.stairTrigger = &trigger;
	auto triggerBbox = trigger.GetBoundingBox();

	// -2: change to idle state when barely hit the floor to make the transition smoother
	if (parent.GetBoundingBox().bottom >= triggerBbox.bottom - 2
		&& (parent.moveState == MoveState::GOING_DOWNSTAIRS || parent.moveState == MoveState::IDLE_DOWNSTAIRS))
	{
		parent.IdleOnGround();

		auto offsetBottom = parent.GetFrameRect().bottom - parent.GetBoundingBox().bottom;
		// TODO: why 1 extra pixel?
		parent.position.y = trigger.GetBoundingBox().bottom - parent.GetFrameRect().Height() + offsetBottom - 1;
		parent.SetDistance_Y(0);
	}
}

void PlayerResponseSystem::OnCollideWithStairDownTrigger(Trigger &trigger, ResponseResult &responseResult)
{
	responseResult.stairTrigger = &trigger;
	auto triggerBbox = trigger.GetBoundingBox();

	if (parent.GetBoundingBox().bottom <= triggerBbox.bottom
		&& (parent.moveState == MoveState::GOING_UPSTAIRS || parent.moveState == MoveState::IDLE_UPSTAIRS))
	{
		parent.IdleOnGround();

		auto offsetBottom = parent.GetFrameRect().bottom - parent.GetBoundingBox().bottom;
		// TODO: why 1 extra pixel?
		parent.position.y = trigger.GetBoundingBox().bottom - parent.GetFrameRect().Height() + offsetBottom;
		parent.SetDistance_Y(0);
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
