#pragma once

#include "ICollisionSystem.h"

namespace Castlevania
{
	class GameObject;

	class CollisionSystem : public ICollisionSystem
	{
	public:
		CollisionSystem(GameObject &parent);

		CollisionData GetCollisionData() override;
		void Update(ObjectCollection &objectCollection) override;

	private:
		GameObject &parent;
		CollisionData collisionData;

		CollisionData FilterCollision(CollisionResults collisionResults);
	};
}