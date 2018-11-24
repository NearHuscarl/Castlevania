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
			timeLeft = Timer(300); // in seconds
			stage = 1;

			playerHealth = MAX_HEALTH;
			bossHealth = MAX_HEALTH;

			secondaryWeapon = EntityType::Unknown;

			hearts = 5;
			lives = 3;
		}

		static PlayerData Default()
		{
			static auto defaultData = PlayerData{};
			return defaultData;
		}

		int score;
		Timer timeLeft; // in seconds
		int stage;

		int playerHealth;
		int bossHealth;

		EntityType secondaryWeapon;

		int hearts;
		int lives;
	};
}