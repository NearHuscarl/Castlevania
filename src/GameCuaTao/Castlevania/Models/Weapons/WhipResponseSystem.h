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
		void Update(ObjectCollection &objectCollection);

	private:
		Whip &parent;

		void OnCollideWithBrazier(CollisionResult &result, ObjectCollection &objectCollection);
		void OnCollideWithEnemy(CollisionResult &result, Player &player);
	};
}