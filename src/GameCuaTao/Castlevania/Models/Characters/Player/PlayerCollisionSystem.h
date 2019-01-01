#pragma once

#include "../../Systems/Collision/CollisionSystem.h"

namespace Castlevania
{
	class GameObject;

	class PlayerCollisionSystem : public CollisionSystem
	{
	public:
		PlayerCollisionSystem(GameObject &parent);

		IGameObject &GetParent() override;
		void Update(UpdateData &updateData) override;

	private:
		IGameObject &parent;
	};
}