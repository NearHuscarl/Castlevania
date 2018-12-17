#include <assert.h>
#include "GiantBat.h"
#include "../../Settings.h"

using namespace Castlevania;

GiantBat::GiantBat() : Enemy{ ObjectId::GiantBat }
{
}

float GiantBat::GetDiveSpeed()
{
	return diveSpeed;
}

void GiantBat::SetDiveSpeed(float speed)
{
	diveSpeed = speed;
}

void GiantBat::SetActive()
{
	isActive = true;
	SendMessageToSystems(ACTIVE_CHANGED);
}

bool GiantBat::IsInRange()
{
	return isInRange;
}

void GiantBat::IsInRange(bool value)
{
	isInRange = value;
}

Rect GiantBat::GetAttackZone()
{
	auto activeArea = Rect{};
	auto originPosition = GetOriginPosition();

	activeArea.left = (int)originPosition.x - attackZone.Width() / 2;
	activeArea.top = (int)originPosition.y - attackZone.Height() / 2;
	activeArea.right = (int)activeArea.left + attackZone.Width();
	activeArea.bottom = (int)activeArea.top + attackZone.Height();

	return activeArea;
}

void GiantBat::SetAttackZone(Rect attackZone)
{
	this->attackZone = attackZone;
}

Rect GiantBat::GetThreatZone()
{
	auto threatArea = Rect{};
	auto originPosition = GetOriginPosition();

	threatArea.left = (int)originPosition.x - threatZone.Width() / 2;
	threatArea.top = (int)originPosition.y - threatZone.Height() / 2;
	threatArea.right = (int)threatArea.left + threatZone.Width();
	threatArea.bottom = (int)threatArea.top + threatZone.Height();

	return threatArea;
}

void GiantBat::SetThreatZone(Rect threatZone)
{
	this->threatZone = threatZone;
}

void GiantBat::SetMoveArea(Rect moveArea)
{
	this->moveArea = moveArea;
}

Rect GiantBat::GetMoveArea()
{
	assert(moveArea != Rect::Empty());

	return moveArea;
}

GiantBatState GiantBat::GetGiantBatState()
{
	return giantBatState;
}

void GiantBat::Update(GameTime gameTime, UpdateData &updateData)
{
	Enemy::Update(gameTime, updateData);

	switch (giantBatState)
	{
		case GiantBatState::FLYING:
			if (isActive)
			{
				flyingDistance -= GetDistance().Length();

				if (flyingDistance <= 0)
					Hover();
			}
			break;
	}
}

void GiantBat::Idle()
{
	velocity = Vector2::Zero();
	SetGiantBatState(GiantBatState::IDLE);
}

void GiantBat::Hover()
{
	velocity = Vector2::Zero();
	SetGiantBatState(GiantBatState::HOVERING);
}

void GiantBat::Fly(float distance)
{
	SetGiantBatState(GiantBatState::FLYING);
	flyingDistance = distance;
}

void GiantBat::Dive(Vector2 playerPosition)
{
	this->playerPosition = playerPosition;
	SetGiantBatState(GiantBatState::DIVING);
}

void GiantBat::Shoot(std::unique_ptr<GameObject> fireball)
{
}

void GiantBat::SetGiantBatState(GiantBatState state)
{
	giantBatState = state;
	SendMessageToSystems(MOVE_STATE_CHANGED);
}
