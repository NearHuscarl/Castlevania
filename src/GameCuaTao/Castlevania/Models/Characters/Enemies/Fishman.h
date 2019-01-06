#pragma once

#include "Direct2DGame/Utilities/Stopwatch.h"
#include "Enemy.h"
#include "../../Weapons/RangedWeapon.h"

namespace Castlevania
{
	enum class FishmanState
	{
		LAUNCHING,
		WALKING,
		FALLING,
		SHOOTING,
	};

	class Fishman : public Enemy
	{
	public:
		Fishman();

		void SetLaunchSpeed(float speed);
		FishmanState GetFishmanState();

		void Update(UpdateData &updateData) override;

		void Launch();
		void WalkRight();
		void WalkLeft();
		void Shoot(std::unique_ptr<RangedWeapon> fireball);

	private:
		float launchSpeed;
		FishmanState fishmanState;
		Stopwatch shootingTimer;

		std::unique_ptr<RangedWeapon> fireball;

		// Fishman animation stop updating when in falling state
		void Freeze();
		void Land();

		void SetFishmanState(FishmanState state);
		void ReleaseFireball();

		friend class FishmanResponseSystem;
	};
}