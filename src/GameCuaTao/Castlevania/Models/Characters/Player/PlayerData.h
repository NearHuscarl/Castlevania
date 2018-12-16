#pragma once

#include <memory>
#include "../../ObjectId.h"

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
			subWeapon = ObjectId::Unknown;
			hearts = 5;
			lives = 3;
		}

		int score;
		int health;
		ObjectId subWeapon;
		int hearts;
		int lives;
	};
}