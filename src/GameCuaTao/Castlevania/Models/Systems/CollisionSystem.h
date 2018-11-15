#pragma once

#include "../Body/CollisionData.h"

namespace Castlevania
{
	class GameObject;
	struct ObjectCollection;

	class CollisionSystem
	{
	public:
		CollisionSystem(GameObject &parent);

		CollisionData GetCollisionData();

		void Update(float deltaTime, ObjectCollection &objectCollection);
		void ResolveCollision(CollisionData collisionData, float deltaTime);

	private:
		GameObject &parent;
		CollisionData collisionData;

		CollisionData FilterCollision(CollisionResults collisionResults);
	};
}