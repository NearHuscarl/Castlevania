#include "Direct2DGame/MathHelper.h"
#include "GiantBatControlSystem.h"
#include "../../UpdateData.h"
#include "../../Settings.h"

using namespace Castlevania;

constexpr auto MIN_DISTANCE = 70.0f;
constexpr auto MAX_DISTANCE = 230.0f;

constexpr auto MIN_HOVERING_TIME = 500;
constexpr auto MAX_HOVERING_TIME = 2500;

constexpr auto MIN_SPEED = 50.0f;
constexpr auto MAX_SPEED = 500.0f;

constexpr auto LOWER_BOUND_DISTANCE_TO_PLAYER = 32;  // 1 tile
constexpr auto UPPER_BOUND_DISTANCE_TO_PLAYER = 352; // 11 tiles

GiantBatControlSystem::GiantBatControlSystem(GiantBat &parent, ObjectFactory &objectFactory) :
	parent{ parent },
	objectFactory{ objectFactory }
{
	auto speed = parent.GetSpeed();

	minSpeed = MathHelper::Max(speed - 75.0f, MIN_SPEED);
	maxSpeed = MathHelper::Min(speed + 70.0f, MAX_SPEED);
}

void GiantBatControlSystem::Receive(int message)
{
	switch (message)
	{
		case MOVE_STATE_CHANGED:
			OnMoveStateChanged();
			break;

		case ACTIVE_CHANGED:
			OnActiveChanged();
			break;

		case PLAYER_IN_THREAT_ZONE:
			if (parent.GetGiantBatState() != GiantBatState::DIVING)
				parent.Dive(playerPosition);
			break;
	}
}

void GiantBatControlSystem::Update(UpdateData &updateData)
{
	auto player = updateData.player;
	playerPosition = player->GetPosition();

	switch (parent.GetGiantBatState())
	{
		case GiantBatState::HOVERING:
			if (hoveringTimer.ElapsedMilliseconds() >= hoveringTime)
			{
				if (!parent.IsInRange())
				{
					parent.Shoot(objectFactory.CreateFireball(), player->GetOriginPosition());
				}
				else
					parent.Dive(playerPosition);

				hoveringTimer.Reset();
			}
			break;

		case GiantBatState::FLYING:
			ClampMoveInArea();
			break;

		case GiantBatState::DIVING:
		{
			auto velocity = parent.GetVelocity();
			auto position = parent.GetPosition();

			if (velocity.y < 0 && position.y <= heightToStopDiving)
				MoveRandomly();

			ClampMoveInArea();
		}
	}
}

void GiantBatControlSystem::OnMoveStateChanged()
{
	switch (parent.GetGiantBatState())
	{
		case GiantBatState::HOVERING:
			hoveringTime = MathHelper::RandomBetween(MIN_HOVERING_TIME, MAX_HOVERING_TIME);
			hoveringTimer.Restart();
			break;

		case GiantBatState::DIVING:
			heightToStopDiving = parent.GetPosition().y + MathHelper::RandomBetween(20, 40);
			break;
	}
}

void GiantBatControlSystem::OnActiveChanged()
{
	if (MathHelper::RandomBoolean())
		parent.Hover();
	else
		MoveRandomly();
}

bool GiantBatControlSystem::IsDistanceOutsideOfViewport(Vector2 distance)
{
	auto position = parent.GetPosition();
	auto newPosition = position + distance;
	auto newBbox = parent.GetSprite()->GetBoundingRectangle(newPosition);
	auto moveArea = (RectF)parent.GetMoveArea();

	if (!moveArea.Contains(newBbox))
		return true;
	else
		return false;
}

bool GiantBatControlSystem::IsBelowPlayer()
{
	return parent.GetPosition().y >= playerPosition.y;
}

float GiantBatControlSystem::GetSpeedRelativeToPlayerDistance()
{
	auto position = parent.GetPosition();
	auto distanceToPlayer = Vector2::Distance(position, playerPosition);
	auto distanceWeight = (distanceToPlayer - LOWER_BOUND_DISTANCE_TO_PLAYER) /
		(UPPER_BOUND_DISTANCE_TO_PLAYER - LOWER_BOUND_DISTANCE_TO_PLAYER);

	// the closer the player is the quicker the boss moves
	return MathHelper::Lerp(maxSpeed, minSpeed, distanceWeight);
}

void GiantBatControlSystem::MoveRandomly()
{
	parent.SetSpeed(GetSpeedRelativeToPlayerDistance());

	auto direction = RandomDirection();
	auto distance = MathHelper::RandomBetween(MIN_DISTANCE, MAX_DISTANCE);

	while (IsDistanceOutsideOfViewport(direction * distance))
	{
		direction = RandomDirection();
		distance = MathHelper::RandomBetween(MIN_DISTANCE, MAX_DISTANCE);
	}

	parent.SetDirection(direction);
	parent.Fly(distance);
}

void GiantBatControlSystem::ClampMoveInArea()
{
	auto boundingBox = parent.GetBoundingBox();
	auto moveArea = parent.GetMoveArea();

	if (boundingBox.left <= moveArea.left + 4)
		parent.SetFacing(Facing::Right);

	if (boundingBox.right >= moveArea.right - 4)
		parent.SetFacing(Facing::Left);
}

Vector2 GiantBatControlSystem::RandomDirection()
{
	if (IsBelowPlayer())
		return MathHelper::RandomDirection(225, 315);
	else
		return MathHelper::RandomDirection();
}
