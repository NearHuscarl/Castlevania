#pragma once

#include "SpawnArea.h"

namespace Castlevania
{
	class VampireBatSpawnArea : public SpawnArea
	{
	public:
		VampireBatSpawnArea(ObjectFactory &objectFactory);
		
		void SetGroupSpawnTime(int groupSpawnTime) override;

	private:
		int originalGroupSpawnTime;

		void SpawnObject(UpdateData &updateData) override;
	};
}