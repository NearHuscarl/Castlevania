#pragma once

#include "../Utilities/Timer.h"

namespace Castlevania
{
	struct GameplayData
	{
		GameplayData()
		{
			timeLeft = Timer{ 300 };
			stage = 1;
		}

		Timer timeLeft;
		int stage; // In-game stage number. It has nothing to do with Stage class.
		// This is the current stage count in game while the Stage class manages
		// everything in the current map. TODO: maybe rename the class to sth else
	};
}