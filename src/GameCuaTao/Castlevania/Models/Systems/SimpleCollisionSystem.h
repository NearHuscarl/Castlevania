#pragma once

#include "Direct2DGame/Extensions/Collisions/Body/CollisionData.h"
#include "ICollisionSystem.h"

namespace Castlevania
{
	class GameObject;

	// A collision detection system for static objects only
	class SimpleCollisionSystem : public ICollisionSystem
	{
	public:
		SimpleCollisionSystem(GameObject &parent);

		void Update(ObjectCollection &objectCollection) override;

	protected:
		GameObject &parent;

		void CalculateCollision(GameObject &gameObject, CollisionResults &results);
	};
}