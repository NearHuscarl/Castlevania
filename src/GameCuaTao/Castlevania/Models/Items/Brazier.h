#pragma once

#include "Powerup.h"

namespace Castlevania
{
	class Brazier : public GameObject
	{
	public:
		Brazier();

		void SetSpawnedItem(std::unique_ptr<Powerup> item);
		void OnBeingHit();
		void Update(GameTime gameTime, UpdateData &updateData) override;

	private:
		std::unique_ptr<Powerup> item;
		
		std::unique_ptr<GameObject> SpawnItem(); // Spawn item and disappear after hit by player
	};
}