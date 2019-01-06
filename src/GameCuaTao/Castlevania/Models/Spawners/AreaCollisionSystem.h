#pragma once

#include "../Systems/Collision/ICollisionSystem.h"
#include "../GameObject.h"

namespace Castlevania
{
	class AreaCollisionSystem : public ICollisionSystem
	{
	public:
		AreaCollisionSystem(GameObject &parent);

		void Receive(int message) override {};
		void Update(UpdateData &updateData) override;

	protected:
		GameObject &parent;
		bool wasPlayerInSpawnZone;
	};
}