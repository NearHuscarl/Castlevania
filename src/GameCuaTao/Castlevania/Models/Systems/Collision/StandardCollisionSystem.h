#pragma once

#include "Direct2DGame/Extensions/Collisions/Body/CollisionData.h"
#include "CollisionSystem.h"

namespace Castlevania
{
	class GameObject;

	// Check for collision with game object (simon, bat, weapon...) and boundary (wall, floor, ...)
	class StandardCollisionSystem : public CollisionSystem
	{
	public:
		StandardCollisionSystem(GameObject &parent);

		void Update(ObjectCollection &objectCollection) override;
	};
}