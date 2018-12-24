#pragma once

#include "../Systems/CollisionResponse/ICollisionResponseSystem.h"
#include "HolyWater.h"

namespace Castlevania
{
	class Player;

	class HolyWaterResponseSystem : public ICollisionResponseSystem
	{
	public:
		HolyWaterResponseSystem(HolyWater &parent);
		
		void Receive(int message) override {};
		void Update(UpdateData &updateData) override;

	private:
		HolyWater &parent;
		
		void OnCollideWithBoundary(CollisionResult &result);
		void OnCollideWithBrazier(CollisionResult &result);
		void OnCollideWithEnemy(CollisionResult &result, Player &player);
		void OnCollideWithFireball(CollisionResult &result);
	};
}