#pragma once

#include "CollisionSystem.h"

namespace Castlevania
{
	class GameObject;

	// Only check for collision with static object (wall, floor, platform)
	class StaticCollisionSystem : public CollisionSystem
	{
	public:
		StaticCollisionSystem(GameObject &parent);

		void Update(ObjectCollection &objectCollection) override;
	};
}