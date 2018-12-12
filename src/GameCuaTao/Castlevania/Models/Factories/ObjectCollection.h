#pragma once

#include "../Characters/Player/Player.h"
#include "../Trigger.h"

namespace Castlevania
{
	struct ObjectCollection
	{
		std::shared_ptr<Player> player;
		std::vector<std::unique_ptr<GameObject>> boundaries;
		std::vector<std::unique_ptr<Trigger>> triggers;
		std::vector<std::unique_ptr<GameObject>> entities;
		std::vector<std::unique_ptr<GameObject>> viewportAreas;
		std::vector<std::unique_ptr<GameObject>> foregroundObjects;
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