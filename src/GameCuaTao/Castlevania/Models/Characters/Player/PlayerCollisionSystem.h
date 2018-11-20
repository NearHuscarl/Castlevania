#pragma once

#include "Direct2DGame/Extensions/Collisions/Body/CollisionData.h"
#include "../../Systems/Collision/CollisionSystem.h"

namespace Castlevania
{
	class GameObject;

	// Check for collision with all objects in game
	class PlayerCollisionSystem : public CollisionSystem
	{
	public:
		PlayerCollisionSystem(GameObject &parent);

		void Update(ObjectCollection &objectCollection) override;
	};
}