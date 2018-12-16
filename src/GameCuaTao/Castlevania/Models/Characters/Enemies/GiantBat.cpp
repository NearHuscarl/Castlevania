#include "GiantBat.h"
#include "../../Settings.h"

using namespace Castlevania;

GiantBat::GiantBat() : Enemy{ ObjectId::GiantBat }
{
}

void GiantBat::SetDiveSpeed(float speed)
{
	diveSpeed = speed;
}

void GiantBat::SetActive()
{
	Hover();
}

bool GiantBat::IsInRange()
{
	return isInRange;
}

void GiantBat::IsInRange(bool value)
{
	isInRange = value;
}

Rect GiantBat::GetAttackArea()
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

GiantBatState GiantBat::GetGiantBatState()
{
	return giantBatState;
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

void GiantBat::FlyTo(Vector2 position)
{
	//velocity.x = speed;
	SetGiantBatState(GiantBatState::FLYING);
}

void GiantBat::Dive(Vector2 vertex)
{
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
