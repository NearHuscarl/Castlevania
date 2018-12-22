#include "Panther.h"
#include "../../UpdateData.h"
#include "../../Settings.h"

using namespace Castlevania;

Panther::Panther() : Enemy{ ObjectId::Panther }
{
	playerDirection = Direction::None;
	Idle();
}

RectF Panther::GetActiveZone()
{
	auto activeArea = RectF{};
	auto originPosition = GetOriginPosition();

	activeArea.left = originPosition.x - activeZone.Width() / 2;
	activeArea.top = originPosition.y - activeZone.Height() / 2;
	activeArea.right = activeArea.left + activeZone.Width();
	activeArea.bottom = activeArea.top + activeZone.Height();

	return activeArea;
}

void Panther::SetActiveZone(Rect activeZone)
{
	this->activeZone = activeZone;
}

void Panther::SetJumpSpeed(float speed)
{
	this->jumpSpeed = speed;
}

bool Panther::IsActive()
{
	return isActive;
}

void Panther::SetActive(bool value)
{
	isActive = value;
}

PantherState Panther::GetPantherState()
{
	return pantherState;
}

Direction Panther::GetPlayerDirection()
{
	return playerDirection;
}

void Panther::Update(UpdateData &updateData)
{
	Enemy::Update(updateData);

	auto player = updateData.player;

	if (player->GetOriginPosition().x <= GetOriginPosition().x)
		playerDirection = Direction::Left;
	else
		playerDirection = Direction::Right;
}

void Panther::Idle()
{
	velocity.x = 0.0f;
	SetPantherState(PantherState::IDLE);
}

void Panther::RunRight()
{
	SetFacing(Facing::Right);
	velocity.x = speed;
	SetPantherState(PantherState::RUNNING);
}

void Panther::RunLeft()
{
	SetFacing(Facing::Left);
	velocity.x = -speed;
	SetPantherState(PantherState::RUNNING);
}

void Panther::Jump()
{
	velocity.y = -jumpSpeed;
	SetDistance_Y(0);
	SetPantherState(PantherState::JUMPING);
}

void Panther::Land()
{
	if (isActive)
	{
		if (playerDirection == Direction::Left)
			RunLeft();
		else
			RunRight();
	}
	else
		Idle(); // panther falls to the ground when loading map dont register as an actual landing
}

void Panther::SetPantherState(PantherState state)
{
	pantherState = state;
	SendMessageToSystems(MOVE_STATE_CHANGED);
}
