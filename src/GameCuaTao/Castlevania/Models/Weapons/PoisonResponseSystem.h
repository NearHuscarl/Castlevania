#pragma once

#include "../Systems/CollisionResponse/ICollisionResponseSystem.h"
#include "../Weapons/RangedWeapon.h"

namespace Castlevania
{
	class Player;

	// Weapons that damages the creature repeatedly over time
	class PoisonResponseSystem : public ICollisionResponseSystem
	{
	public:
		PoisonResponseSystem(RangedWeapon &parent);

		virtual void Receive(int message) override {};
		void Update(UpdateData &updateData) override;

	private:
		RangedWeapon &parent;

		void OnCollideWithBrazier(CollisionResult &result);
		void OnCollideWithEnemy(CollisionResult &result, Player &player);
		void OnCollideWithFireball(CollisionResult &result);
	};
}