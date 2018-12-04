#pragma once

#include "../../Systems/Collision/CollisionSystem.h"

namespace Castlevania
{
	class Panther;

	// Only check for collision with static object (wall, floor, platform)
	class PantherCollisionSystem : public CollisionSystem
	{
	public:
		PantherCollisionSystem(Panther &parent);

		IGameObject &GetParent() override;
		void Update(ObjectCollection &objectCollection) override;

	private:
		Panther &parent;
	};
}