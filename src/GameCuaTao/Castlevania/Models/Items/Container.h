#pragma once

#include "../PowerupGenerator.h"

namespace Castlevania
{
	class Container : public GameObject
	{
	public:
		Container(ObjectId type, std::unique_ptr<PowerupGenerator> powerupGenerator);

		void SetSpawningState(ObjectState spawningState);
		void SetSpawnedItem(ObjectId powerupType);
		void OnBeingHit();
		void Update(UpdateData &updateData) override;

	private:
		ObjectId powerupType;
		ObjectState spawningState; // Determine the state to trigger spawning item (DYING or DEAD)
		std::unique_ptr<PowerupGenerator> powerupGenerator;

		void SpawnItem(); // Spawn item and disappear after hit by player
	};
}