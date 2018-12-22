#pragma once

#include "../GameObject.h"

namespace Castlevania
{
	struct ObjectCollection
	{
		// wall, floor, ground, platform...
		std::vector<std::unique_ptr<GameObject>> blocks;

		// Dumb objects that dont need to run Update()
		std::vector<std::unique_ptr<GameObject>> staticObjects;

		// Regular game objects: enemy, candle, powerup...
		std::vector<std::unique_ptr<GameObject>> entities;

		// For aesthetic purpose only
		std::vector<std::unique_ptr<GameObject>> foregroundObjects;

		void Clear()
		{
			staticObjects.clear();
			entities.clear();
			foregroundObjects.clear();
		}
	};
}