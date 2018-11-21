#pragma once

#include "Direct2DGame/Extensions/Collisions/Body/CollisionData.h"
#include "CollisionSystem.h"

namespace Castlevania
{
	class GameObject;

	// Only check for collision with normal game object (simon, bat, weapon...)
	class EntityCollisionSystem : public CollisionSystem
	{
	public:
		EntityCollisionSystem(GameObject &parent);

		void Update(ObjectCollection &objectCollection) override;
	};
}