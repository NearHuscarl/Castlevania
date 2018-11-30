#pragma once

#include "CollisionSystem.h"

namespace Castlevania
{
	class GameObject;

	// A collision detection system for static objects only
	class SimpleCollisionSystem : public CollisionSystem
	{
	public:
		SimpleCollisionSystem(GameObject &parent);

		void Update(ObjectCollection &objectCollection) override;
	};
}