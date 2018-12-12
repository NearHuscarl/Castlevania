#pragma once

#include "../../Items/Door.h"
#include "../../Trigger.h"

namespace Castlevania
{
	// Some collision result with important objects will be saved
	// for future references
	struct NearbyObjects
	{
		Trigger *stair = nullptr;
		Direction stairHitDirection = Direction::None;

		Door *door = nullptr;
		Direction doorHitDirection = Direction::None;
	};
}