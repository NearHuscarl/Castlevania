#include "Panther.h"
#include "../../UpdateData.h"
#include "../../Settings.h"

using namespace Castlevania;

constexpr auto ACTIVE_ZONE_WIDTH = 250;
constexpr auto ACTIVE_ZONE_HEIGHT = 410;
constexpr auto JUMP_SPEED = 200.0f;

Panther::Panther() : Enemy{ EntityType::Panther }
{
	playerDirection = Direction::None;
	Idle();
}

bool Panther::IsActive()
{
	return isActive;
}

void Panther::SetActive(bool value)
{
	isActive = value;
}

RectF Panther::GetActiveArea()
{
	auto activeArea = RectF{};
	auto originPosition = GetOriginPosition();

	activeArea.left = originPosition.x - ACTIVE_ZONE_WIDTH / 2;
	activeArea.top = originPosition.y - ACTIVE_ZONE_HEIGHT / 2;
	activeArea.right = activeArea.left + ACTIVE_ZONE_WIDTH;
	activeArea.bottom = activeArea.top + ACTIVE_ZONE_HEIGHT;

	return activeArea;
}

PantherState Panther::GetPantherState()
{
	return pantherState;
}

Direction Panther::GetPlayerDirection()
{
	return playerDirection;
}

void Panther::Update(GameTime gameTime, UpdateData &updateData)
{
	Enemy::Update(gameTime, updateData);

	auto player = updateData.objectCollection->player;

	if (player->GetBoundingBox().right <= GetOriginPosition().x)
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
	velocity.y = -JUMP_SPEED;
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
