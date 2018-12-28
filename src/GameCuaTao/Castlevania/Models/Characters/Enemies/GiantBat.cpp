#include <assert.h>
#include "GiantBat.h"
#include "../../UpdateData.h"
#include "../../Settings.h"
#include "../../../Utilities/CollisionGrid.h"
#include "../../../Scenes/Stages/StageEvent.h"

using namespace Castlevania;

constexpr auto MIN_DIVING_RANGE = 10;
constexpr auto DIVING_ADJUSTED_DISTANCE = 40;
constexpr auto RISING_SPEED = 250;
constexpr auto SHOOTING_TIME = 1700;

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

void GiantBat::Update(UpdateData &updateData)
{
	Enemy::Update(updateData);

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

		case GiantBatState::RISING:
			if (playerPosition.y - position.y >= DIVING_ADJUSTED_DISTANCE)
			{
				velocity.y = 0;
				DoDiveAttack();
			}
			break;

		case GiantBatState::SHOOTING:
			if (shootingTimer.ElapsedMilliseconds() > SHOOTING_TIME)
			{
				ReleaseFireball();
				Hover();
				shootingTimer.Reset();
			}
			break;
	}

	if (state == ObjectState::DEAD)
		Notify(BOSS_DIE);
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

	if (playerPosition.y - position.y <= MIN_DIVING_RANGE)
		Rise();
	else
		DoDiveAttack();
}

void GiantBat::Shoot(std::unique_ptr<RangedWeapon> fireball, Vector2 destination)
{
	auto fireballPosition = GetOriginPosition();
	auto direction = Vector2::Normalize(destination - fireballPosition);
	auto fireballSpeed = fireball->GetThrowVelocity().x;
	
	if (direction.x > 0)
		fireball->SetFacing(Facing::Right);
	else
		fireball->SetFacing(Facing::Left);

	fireball->SetThrowVelocity(direction * fireballSpeed);
	fireball->SetPosition(fireballPosition);

	this->fireball = std::move(fireball);

	SetGiantBatState(GiantBatState::SHOOTING);
	shootingTimer.Start();
}

void GiantBat::SetGiantBatState(GiantBatState state)
{
	giantBatState = state;
	SendMessageToSystems(MOVE_STATE_CHANGED);
}

void GiantBat::Rise()
{
	velocity.x = 0;
	velocity.y = -RISING_SPEED;
	SetGiantBatState(GiantBatState::RISING);
}

void GiantBat::DoDiveAttack()
{
	SetGiantBatState(GiantBatState::DIVING);
}

void GiantBat::ReleaseFireball()
{
	if (fireball == nullptr)
		return;

	fireball->Throw(fireball->GetPosition());
	collisionGrid->Add(std::move(fireball), CollisionObjectType::Entity);
}
