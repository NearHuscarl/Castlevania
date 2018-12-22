#pragma once

#include "../Models/GameObject.h"

namespace Castlevania
{
	using UGameObjects = std::list<std::unique_ptr<GameObject>>;
	using SGameObjects = std::list<std::shared_ptr<GameObject>>;

	struct CollisionObject
	{
		// wall, floor, ground, platform...
		SGameObjects blocks;

		// Dumb objects that dont need to run Update()
		UGameObjects staticObjects;

		// Regular game objects: enemy, candle, powerup...
		UGameObjects entities;

		void RemoveDeadEntities()
		{
			for (auto it = entities.end(); it != entities.begin(); )
			{
				std::advance(it, -1);
				auto object = (*it).get();

				if (object->GetState() == ObjectState::DEAD)
				{
					it = entities.erase(it);
				}
			}
		};
	};
}