#pragma once

#include "../Characters/Player/Player.h"
#include "../Trigger.h"

namespace Castlevania
{
	struct ObjectCollection
	{
		std::shared_ptr<Player> player;

		// Dumb objects that dont need to run Update()
		std::vector<std::unique_ptr<GameObject>> staticObjects;

		// Regular game objects: enemy, candle, powerup...
		std::vector<std::unique_ptr<GameObject>> entities;

		// For aesthetic purpose only
		std::vector<std::unique_ptr<GameObject>> foregroundObjects;
		
		std::vector<std::unique_ptr<GameObject>> stageAreas;
		std::map<std::string, Vector2> locations;

		void RemoveDeadObjects()
		{
			for (int i = entities.size() - 1; i >= 0; i--)
			{
				auto &entity = entities[i];

				if (entity->GetState() == ObjectState::DEAD)
					entities.erase(entities.begin() + i);
			}
		}
	};
}