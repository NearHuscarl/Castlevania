#pragma once

#include "ICollisionSystem.h"

namespace Castlevania
{
	class GameObject;

	class CollisionSystem : public ICollisionSystem
	{
	public:
		CollisionSystem(GameObject &parent);

		CollisionData GetCollisionData();
		void Update(ObjectCollection &objectCollection);

	protected:
		GameObject &parent;
		CollisionData collisionData;

		CollisionData FilterCollision(CollisionResults collisionResults);
	};
}