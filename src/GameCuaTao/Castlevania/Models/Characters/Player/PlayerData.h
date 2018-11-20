#pragma once

#include <memory>
#include "../../GameObject.h"
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

		std::unique_ptr<GameObject> secondaryWeapon = nullptr;

		int hearts = 5;
		int p = 3; // TODO: what is P
	};
}