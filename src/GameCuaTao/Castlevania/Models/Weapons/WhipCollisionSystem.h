#pragma once

#include "Direct2DGame/Extensions/Collisions/Body/CollisionData.h"
#include "../Systems/Collision/ICollisionSystem.h"
#include "../GameObject.h"

namespace Castlevania
{
	class IGameObject;

	// Collision detection method: simple rectangle instesect check
	// Use sprite frame instead of bounding box TODO: explain
	class WhipCollisionSystem : public ICollisionSystem
	{
	public:
		WhipCollisionSystem(GameObject &parent);

		void Receive(int message) override {};
		void Update(ObjectCollection &objectCollection) override;

	protected:
		GameObject &parent;
	};
}