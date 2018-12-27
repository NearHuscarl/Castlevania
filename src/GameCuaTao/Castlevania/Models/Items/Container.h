#pragma once

#include "Powerup.h"

namespace Castlevania
{
	class Container : public GameObject
	{
	public:
		Container(ObjectId type);

		void SetSpawningState(ObjectState spawningState);
		void SetSpawnedItem(std::unique_ptr<Powerup> item);
		void OnBeingHit();
		void Update(UpdateData &updateData) override;

	private:
		std::unique_ptr<Powerup> item;
		ObjectState spawningState; // Determine the state to trigger spawning item (DYING or DEAD)
		
		std::unique_ptr<GameObject> SpawnItem(); // Spawn item and disappear after hit by player
	};
}