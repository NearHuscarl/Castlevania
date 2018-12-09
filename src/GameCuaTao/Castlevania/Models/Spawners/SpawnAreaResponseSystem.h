#pragma once

#include "../Systems/CollisionResponse/ICollisionResponseSystem.h"
#include "SpawnArea.h"

namespace Castlevania
{
	class Player;

	class SpawnAreaResponseSystem : public ICollisionResponseSystem
	{
	public:
		SpawnAreaResponseSystem(SpawnArea &parent);

		virtual void Receive(int message) override {};
		void Update(UpdateData &updateData) override;

	private:
		SpawnArea &parent;
	};
}