#pragma once

#include "Direct2DGame/Extensions/Collisions/Body/CollisionData.h"
#include "../Systems/Collision/ICollisionSystem.h"
#include "../GameObject.h"

namespace Castlevania
{
	class SpawnerCollisionSystem : public ICollisionSystem
	{
	public:
		SpawnerCollisionSystem(GameObject &parent);

		void Receive(int message) override {};
		void Update(UpdateData &updateData) override;

	protected:
		GameObject &parent;
	};
}