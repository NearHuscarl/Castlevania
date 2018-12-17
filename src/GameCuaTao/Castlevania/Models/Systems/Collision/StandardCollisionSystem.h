#pragma once

#include "CollisionSystem.h"

namespace Castlevania
{
	class GameObject;

	// Check for collision with game object (simon, bat, weapon...) and boundary (wall, floor, ...)
	class StandardCollisionSystem : public CollisionSystem
	{
	public:
		StandardCollisionSystem(GameObject &parent);

		IGameObject &GetParent() override;
		void Update(UpdateData &updateData) override;

	private:
		IGameObject &parent;
	};
}