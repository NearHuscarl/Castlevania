#include "Fishman.h"
#include "../../UpdateData.h"
#include "../../Settings.h"
#include "../../../Utilities/CollisionGrid.h"

using namespace Castlevania;

constexpr auto SHOOTING_TIME = 600;
constexpr auto RELEASE_FIREBALL_TIME = SHOOTING_TIME / 2;

Fishman::Fishman() : Enemy{ ObjectId::Fishman }
{
}

void Fishman::SetLaunchSpeed(float speed)
{
	launchSpeed = speed;
}

FishmanState Fishman::GetFishmanState()
{
	return fishmanState;
}

void Fishman::Update(UpdateData &updateData)
{
	Enemy::Update(updateData);

	switch (fishmanState)
	{
		case FishmanState::SHOOTING:
			if (shootingTimer.ElapsedMilliseconds() > SHOOTING_TIME)
			{
				if (facing == Facing::Left)
					WalkRight();
				else // facing == Facing::Right
					WalkLeft();

				shootingTimer.Reset();
			}
			else if (shootingTimer.ElapsedMilliseconds() > RELEASE_FIREBALL_TIME)
			{
				if (fireball != nullptr)
					ReleaseFireball();
			}
			break;
	}
}

void Fishman::Launch()
{
	velocity.y = -launchSpeed;
	SetFishmanState(FishmanState::LAUNCHING);
}

void Fishman::WalkRight()
{
	SetFacing(Facing::Right);
	velocity.x = speed;
	SetFishmanState(FishmanState::WALKING);
}

void Fishman::WalkLeft()
{
	SetFacing(Facing::Left);
	velocity.x = -speed;
	SetFishmanState(FishmanState::WALKING);
}

void Fishman::Shoot(std::unique_ptr<RangedWeapon> fireball)
{
	this->fireball = std::move(fireball);
	this->fireball->GetBody().Enabled(false);
	this->fireball->SetVisibility(false);

	velocity.x = 0.0f;
	SetFishmanState(FishmanState::SHOOTING);
	shootingTimer.Start();
}

void Fishman::Freeze()
{
	velocity = Vector2::Zero();
	SetDistance(Vector2::Zero());
	SetFishmanState(FishmanState::FALLING);
}

void Fishman::Land()
{
	if (facing == Facing::Left)
		WalkLeft();
	else
		WalkRight();
}

void Fishman::SetFishmanState(FishmanState state)
{
	fishmanState = state;
	SendMessageToSystems(MOVE_STATE_CHANGED);
}

void Fishman::ReleaseFireball()
{
	fireball->SetFacing(facing);

	auto fishmanRect = GetFrameRect();
	auto position = Vector2{
		fishmanRect.left + 20,
		fishmanRect.top + 6
	};

	fireball->Throw(position);
	collisionGrid->Add(std::move(fireball), CollisionObjectType::Entity);
}
