#pragma once

#include "../Systems/CollisionResponse/ICollisionResponseSystem.h"
#include "Whip.h"

namespace Castlevania
{
	class Player;

	class WhipResponseSystem : public ICollisionResponseSystem
	{
	public:
		WhipResponseSystem(Whip &parent);

		virtual void Receive(int message) override {};
		void Update(UpdateData &updateData) override;

	private:
		Whip &parent;

		void OnCollideWithBrazier(CollisionResult &result, ObjectCollection &objectCollection);
		void OnCollideWithEnemy(CollisionResult &result, Player &player);
		void OnCollideWithFireball(CollisionResult &result);
	};
}