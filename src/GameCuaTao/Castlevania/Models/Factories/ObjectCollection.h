#pragma once

#include <map>
#include <set>
#include "../GameObject.h"
#include "../Trigger.h"

namespace Castlevania
{
	constexpr auto BOUNDARY = "Boundary";
	constexpr auto TRIGGER = "Trigger";
	constexpr auto POSITION = "Position";
	constexpr auto OBJECT = "Object";

	struct ObjectCollection
	{
		std::vector<std::unique_ptr<RectangleObject>> boundaries;
		std::vector<std::unique_ptr<Trigger>> triggers;
		std::vector<std::unique_ptr<GameObject>> entities;
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