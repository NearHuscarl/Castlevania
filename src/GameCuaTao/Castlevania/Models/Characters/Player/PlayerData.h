#pragma once

#include <memory>
#include "../../EntityType.h"
#include "../../../Utilities/Timer.h"

namespace Castlevania
{
	constexpr auto MAX_HEALTH = 16;

	struct PlayerData
	{
	public:
		PlayerData()
		{
			score = 0;
			health = MAX_HEALTH;
			subWeapon = EntityType::Unknown;
			hearts = 5;
			lives = 3;
		}

		int score;
		int health;
		EntityType subWeapon;
		int hearts;
		int lives;
	};
}