#pragma once

#include "Direct2DGame/Extensions/Collisions/Body/CollisionData.h"
#include "ICollisionSystem.h"

namespace Castlevania
{
	class GameObject;

	// A collision detection system for dynamic objects using Swept AABB algorithm
	class CollisionSystem : public ICollisionSystem
	{
	public:
		CollisionSystem(GameObject &parent);

		virtual void Update(ObjectCollection &objectCollection) override = 0;

	protected:
		GameObject &parent;

		void CalculateCollision(GameObject &gameObject, CollisionResults &results);
		CollisionData FilterCollision(CollisionResults collisionResults);
	};
}