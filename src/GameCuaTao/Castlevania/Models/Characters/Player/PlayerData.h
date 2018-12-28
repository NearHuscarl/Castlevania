#pragma once

#include <memory>
#include "../../ObjectId.h"
#include "../../Health.h"

namespace Castlevania
{
	constexpr auto MAX_HEALTH = 16;

	struct PlayerData
	{
	public:
		PlayerData()
		{
			score = 0;
			health = Health{ MAX_HEALTH };
			subWeapon = ObjectId::Unknown;
			powerup = ObjectId::Unknown;
			hearts = 5;
			lives = 3;
		}

		int score;
		Health health;
		ObjectId subWeapon;
		ObjectId powerup;
		int hearts;
		int lives;
	};
}