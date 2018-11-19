#pragma once

#include "../../Systems/ICollisionResponseSystem.h"
#include "Player.h"

namespace Castlevania
{
	class PlayerResponseSystem : public ICollisionResponseSystem
	{
	public:
		PlayerResponseSystem(Player &parent);

		void Update(ObjectCollection &objectCollection) override;

	private:
		Player &parent;

		void ClampDistance_X(CollisionData collisionData, Vector2 &distance);
		void ClampDistance_Y(CollisionData collisionData, Vector2 &distance);
	};
}