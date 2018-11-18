#pragma once

#include "Direct2DGame/Extensions/Collisions/Body/CollisionData.h"
#include "ICollisionSystem.h"

namespace Castlevania
{
	class GameObject;

	class CollisionSystem : public ICollisionSystem
	{
	public:
		CollisionSystem(GameObject &parent);

		void Update(ObjectCollection &objectCollection) override;

	protected:
		GameObject &parent;

		CollisionData FilterCollision(CollisionResults collisionResults);
	};
}