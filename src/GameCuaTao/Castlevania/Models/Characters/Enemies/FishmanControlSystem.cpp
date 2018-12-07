#include "Direct2DGame/MathHelper.h"
#include "FishmanControlSystem.h"
#include "../../UpdateData.h"
#include "../../Settings.h"

using namespace Castlevania;

constexpr auto MIN_SHOOTING_INTERVAL = 1500; // milliseconds
constexpr auto MAX_SHOOTING_INTERVAL = 3000;

FishmanControlSystem::FishmanControlSystem(Fishman &parent, ObjectFactory &objectFactory) :
	parent{ parent },
	objectFactory{ objectFactory }
{
	lastState = parent.GetFishmanState();
}

void FishmanControlSystem::Receive(int message)
{
	switch (message)
	{
		case MOVE_STATE_CHANGED:
			if (parent.GetFishmanState() == FishmanState::WALKING && lastState != FishmanState::FALLING)
			{
				ResetShootingTimer();
			}
			lastState = parent.GetFishmanState();
			break;
	}
}

void FishmanControlSystem::Update(UpdateData &updateData)
{
	switch (parent.GetFishmanState())
	{
		case FishmanState::WALKING:
			if (shootingIntervalTimer.ElapsedMilliseconds() >= shootingInterval)
			{
				auto fireball = objectFactory.CreateFireball();
				parent.Shoot(std::move(fireball));
				ResetShootingTimer();
			}
			break;
	}
}

void FishmanControlSystem::ResetShootingTimer()
{
	shootingInterval = MathHelper::RandomBetween(MIN_SHOOTING_INTERVAL, MAX_SHOOTING_INTERVAL);
	shootingIntervalTimer.Restart();
}
