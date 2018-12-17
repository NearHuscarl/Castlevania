#pragma once

#include "../../Systems/Collision/CollisionSystem.h"

namespace Castlevania
{
	class GiantBat;

	// Only check for collision with static object (wall, floor, platform)
	class GiantBatCollisionSystem : public CollisionSystem
	{
	public:
		GiantBatCollisionSystem(GiantBat &parent);

		IGameObject &GetParent() override;
		void Update(UpdateData &updateData) override;

	private:
		GiantBat &parent;

		bool wasPlayerInAttackZone;
		bool wasPlayerInThreatZone;
	};
}