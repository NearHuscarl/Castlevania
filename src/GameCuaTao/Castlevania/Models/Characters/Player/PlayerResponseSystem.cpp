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
	auto collisionData = parent.GetBody().GetCollisionData();
	auto responseResult = ResponseResult{};

	for (auto result : collisionData.collisionResults)
	{
		auto objectId = (ObjectId)result.collidedObject.GetType();
		auto &collidedObject = result.collidedObject;

		switch (objectId)
		{
			case ObjectId::Boundary:
				OnCollideWithBoundary(result, responseResult);
				break;

			case ObjectId::Trigger:
				OnCollideWithTrigger(result, responseResult);
				break;

			case ObjectId::BossFightArea:
				OnCollideWithBossFightArea(result, (Rect)updateData.viewport);
				break;

			case ObjectId::WaterArea:
				OnCollideWithWaterArea(result, *updateData.stageObject);
				break;

			case ObjectId::Zombie:
			case ObjectId::Panther:
			case ObjectId::Fishman:
			case ObjectId::GiantBat:
				OnCollideWithEnemy(result);
				break;

			case ObjectId::VampireBat:
				OnCollideWithVampireBat(result);
				break;

			case ObjectId::Fireball:
				OnCollideWithFireball(result);
				break;

			case ObjectId::BlueMoneyBag:
			case ObjectId::WhiteMoneyBag:
			case ObjectId::RedMoneyBag:
			case ObjectId::FlashingMoneyBag:
				OnCollideWithMoneyBag(result);
				break;

			case ObjectId::AxeItem:
			case ObjectId::DaggerItem:
			case ObjectId::HolyWaterItem:
			case ObjectId::Stopwatch:
				OnCollideWithSubWeaponItem(result);
				break;

			case ObjectId::Cross:
				OnCollideWithCross(result);
				break;

			case ObjectId::LargeHeart:
				OnCollideWithHeart(result);
				break;

			case ObjectId::SmallHeart:
				OnCollideWithSmallHeart(result);
				break;

			case ObjectId::InvisibleJar:
				OnCollideWithInvisibleJar(result);
				break;
				break;

			case ObjectId::WhipPowerup:
				OnCollideWithWhipPowerup(result);
				break;

			case ObjectId::Door:
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

	if (moveState == MoveState::IDLE || moveState == MoveState::WALKING)
		parent.Fall();
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
					ClampDistance_Y(collisionData);
					parent.Land();
					break;

				case MoveState::FALLING_HARD:
				case MoveState::TAKING_DAMAGE:
					if (parent.velocity.y > 0)
					{
						ClampDistance_Y(collisionData);
						parent.Land();
						
						if (parent.data.health <= 0)
							parent.Die();
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

			if (!parent.IsOnTheAir())
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
			responseResult.nearbyObjects.nextMap = &trigger;
			OnCollideWithNextMapTrigger(trigger);
			break;

		case TriggerType::CASTLE_ENTRANCE:
			OnCollideWithCastleEntranceTrigger(trigger);
			break;
	}
}

void PlayerResponseSystem::OnCollideWithBossFightArea(CollisionResult &result, Rect viewport)
{
	auto &bossFightArea = dynamic_cast<GameObject&>(result.collidedObject);
	auto areaBbox = bossFightArea.GetBoundingBox();

	if (areaBbox.left <= viewport.left && viewport.right <= areaBbox.right)
	{
		parent.Notify(BOSS_FIGHT_CUTSCENE_STARTED);
		bossFightArea.GetBody().Enabled(false);
	}
}

void PlayerResponseSystem::OnCollideWithWaterArea(CollisionResult &result, StageObject &stageObject)
{
	auto &waterArea = dynamic_cast<WaterArea&>(result.collidedObject);
	
	if (result.direction == Direction::Top)
	{
		waterArea.Splash(parent.GetOriginPosition());

		auto waterZone = objectFactory.CreateWaterZone();
		auto waterZonePosition = waterArea.GetOriginPosition();

		waterZone->SetOriginPosition(waterZonePosition);
		stageObject.foregroundObjects.push_back(std::move(waterZone));

		parent.Die();
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
	auto &object = dynamic_cast<RangedWeapon&>(result.collidedObject);
	auto hitDirection = GetPlayerHitDirection(object, result.direction);

	parent.TakeDamage(object.GetAttack(), hitDirection);
}

void PlayerResponseSystem::OnCollideWithMoneyBag(CollisionResult &result)
{
	auto &moneyBag = dynamic_cast<MoneyBag&>(result.collidedObject);
	auto effectPosition = Vector2{
		parent.GetBoundingBox().right - 4,
		parent.GetBoundingBox().top + 3 };

	moneyBag.SetPosition(effectPosition);

	parent.data.score += moneyBag.GetMoney();
}

void PlayerResponseSystem::OnCollideWithSubWeaponItem(CollisionResult &result)
{
	auto &subWeaponItem = dynamic_cast<GameObject&>(result.collidedObject);
	auto itemId = subWeaponItem.GetId();

	subWeaponItem.Destroy();
	parent.SetSubWeapon(itemId);
}

void PlayerResponseSystem::OnCollideWithCross(CollisionResult &result)
{
	auto &cross = dynamic_cast<GameObject&>(result.collidedObject);

	parent.Notify(CROSS_POWERUP_ACTIVATED);
	cross.Destroy();
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

void PlayerResponseSystem::OnCollideWithInvisibleJar(CollisionResult &result)
{
	auto &invisibleJar = dynamic_cast<GameObject&>(result.collidedObject);

	parent.BecomeInvisible();
	invisibleJar.Destroy();
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
		whip->SetLevel(WHIP_MAX_LEVEL);
	}

	whipPowerup.Destroy();
}

void PlayerResponseSystem::OnCollideWithDoor(CollisionResult &result, ResponseResult &responseResult)
{
	auto &door = dynamic_cast<Door&>(result.collidedObject);
	auto collisionData = parent.GetBody().GetCollisionData();

	ClampDistance_X(collisionData);

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
