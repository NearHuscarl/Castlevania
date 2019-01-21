#pragma once

#include "CollisionSystem.h"

namespace Castlevania
{
	class GameObject;

	// Check for collision with game objects (simon, bat, weapon...) and blocks (wall, floor, ...)
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