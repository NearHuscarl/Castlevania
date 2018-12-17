#include "Direct2DGame/MathHelper.h"
#include "GiantBatControlSystem.h"
#include "../../UpdateData.h"
#include "../../Settings.h"

using namespace Castlevania;

constexpr auto MIN_DISTANCE = 70.0f;
constexpr auto MAX_DISTANCE = 230.0f;

constexpr auto MIN_HOVERING_TIME = 500;
constexpr auto MAX_HOVERING_TIME = 2500;

GiantBatControlSystem::GiantBatControlSystem(GiantBat &parent, ObjectFactory &objectFactory) :
	parent{ parent },
	objectFactory{ objectFactory }
{
	originalSpeed = parent.GetSpeed();
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
	}
}

void GiantBatControlSystem::Update(UpdateData &updateData)
{
	auto player = updateData.objectCollection->player;
	auto playerPosition = player->GetPosition();

	isBelowPlayer = (parent.GetPosition().y >= playerPosition.y);

	switch (parent.GetGiantBatState())
	{
		case GiantBatState::HOVERING:
			if (hoveringTimer.ElapsedMilliseconds() >= hoveringTime)
			{

				parent.Dive(playerPosition);
				heightToStopDiving = parent.GetPosition().y + MathHelper::RandomBetween(20, 40);
				hoveringTimer.Reset();
			}
			break;

		case GiantBatState::DIVING:
		{
			auto velocity = parent.GetVelocity();
			auto position = parent.GetPosition();

			if (velocity.y < 0 && position.y <= heightToStopDiving)
			{
				auto distanceToPlayer = Vector2::Distance(position, playerPosition);
				auto speed = originalSpeed * (1 / distanceToPlayer) * 20;

				parent.SetSpeed(speed);
				MoveRandomly();
			}
			break;
		}
	}
}

void GiantBatControlSystem::OnMoveStateChanged()
{
	switch (parent.GetGiantBatState())
	{
		case GiantBatState::HOVERING:
			hoveringTime = MathHelper::RandomBetween(MIN_HOVERING_TIME, MAX_HOVERING_TIME);
			hoveringTimer.Start();
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

void GiantBatControlSystem::MoveRandomly()
{
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

Vector2 GiantBatControlSystem::RandomDirection()
{
	if (isBelowPlayer)
		return MathHelper::RandomDirection(225, 315);
	else
		return MathHelper::RandomDirection();
}
