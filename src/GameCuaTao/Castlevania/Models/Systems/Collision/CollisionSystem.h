#pragma once

#include "Direct2DGame/Extensions/Collisions/Body/CollisionData.h"
#include "ICollisionSystem.h"

namespace Castlevania
{
	class GameObject;

	// A collision detection system using Swept AABB algorithm for dynamic objects
	class CollisionSystem : public ICollisionSystem
	{
	public:
		CollisionSystem(GameObject &parent);

		virtual void Receive(int message) override {};
		virtual void Update(ObjectCollection &objectCollection) override = 0;

	protected:
		GameObject &parent;

		void CalculateCollision(GameObject &gameObject, CollisionResults &results);
		// Use simple rectangle intersect check first to calculate collision between two static objects
		bool CalculateStaticCollision(GameObject &gameObject, CollisionResults &results);
		// Use Swept AABB algorithm to calculate collision between a dynamic object with another object
		bool CalculateDynamicCollision(GameObject &gameObject, CollisionResults &results);

		CollisionData FilterCollision(CollisionResults collisionResults);
	};
}