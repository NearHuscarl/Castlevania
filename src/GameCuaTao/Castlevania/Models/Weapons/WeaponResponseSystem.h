#pragma once

#include "../Systems/CollisionResponse/ICollisionResponseSystem.h"
#include "../Characters/Player/Player.h"

namespace Castlevania
{
	class Enemy;

	class WeaponResponseSystem : public ICollisionResponseSystem
	{
	public:
		WeaponResponseSystem(GameObject &parent, bool destroyOnHit);

		virtual void Receive(int message) override;
		void Update(UpdateData &updateData) override;

	private:
		GameObject &parent;
		std::vector<Enemy*> hitEnemies;
		bool destroyOnHit;

		void OnCollideWithBrazier(CollisionResult &result);
		void OnCollideWithEnemy(CollisionResult &result, Player &player);
		void OnCollideWithFireball(CollisionResult &result);
	};
}