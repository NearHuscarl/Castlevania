#pragma once

#include "../AnimatedObject.h"

namespace Castlevania
{
	class FirePit : public AnimatedObject
	{
	public:
		FirePit();

		void SetSpawnedItem(std::unique_ptr<GameObject> item);

		void LoadContent(ContentManager &content) override;
		void Update(float deltaTime, ObjectCollection *objectCollection) override;

		// Spawn item and disappear after hit by player
		std::unique_ptr<GameObject> SpawnItem();

	private:
		std::unique_ptr<GameObject> item;
	};
}