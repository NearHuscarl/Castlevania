#pragma once

#include "../Models/GameObject.h"

namespace Castlevania
{
	using GameObjects = std::list<std::unique_ptr<GameObject>>;

	struct CollisionObject
	{
		// Dumb objects that dont need to run Update()
		// Example: blocks, triggers
		GameObjects staticObjects;

		// Game objects that are interactive and mostly moveable:
		// Example: enemies, candles, weapons, powerups,...
		GameObjects entities;
	};
}