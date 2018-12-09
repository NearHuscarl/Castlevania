#pragma once

#include "SpawnArea.h"

namespace Castlevania
{
	class VampireBatSpawnArea : public SpawnArea
	{
	public:
		VampireBatSpawnArea(ObjectFactory &objectFactory);

	private:
		void SpawnObject(UpdateData &updateData) override;
	};
}