#pragma once

#include <memory>
#include "../../EntityType.h"
#include "../../../Utilities/Timer.h"

namespace Castlevania
{
	struct PlayerData
	{
	public:
		int score = 0;
		Timer timeLeft = Timer(300); // in seconds
		int stage = 1;

		int playerHealth = 16;
		int bossHealth = 16;

		EntityType secondaryWeapon = EntityType::Unknown;

		int hearts = 5;
		int p = 3; // TODO: what is P
	};
}