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

	private:
		GameObject &parent;
		CollisionData collisionData;

		CollisionData FilterCollision(CollisionResults collisionResults);
	};
}