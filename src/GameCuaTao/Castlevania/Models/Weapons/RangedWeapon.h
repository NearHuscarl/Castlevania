#pragma once

#include "../GameObject.h"
#include "../IAttackable.h"
#include "../IThrowable.h"

namespace Castlevania
{
	// Throwable weapon like Dagger, Axe, Boomerang,...
	class RangedWeapon : public GameObject, public IAttackable
	{
	public:
		RangedWeapon(ObjectId type);

		Vector2 GetThrowVelocity();
		void SetThrowVelocity(Vector2 velocity);
		int GetAttack() override;
		void SetAttack(int attack) override;

		void Update(UpdateData &updateData) override;
		void Throw(Vector2 position);

	private:
		Vector2 throwVelocity;
		int attack;
	};
}