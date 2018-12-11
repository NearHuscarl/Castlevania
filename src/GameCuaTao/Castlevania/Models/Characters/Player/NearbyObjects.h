#pragma once

#include "../../Items/Door.h"
#include "../../Trigger.h"

namespace Castlevania
{
	// Some important objects will be saved here from collision response result
	// for future references
	struct NearbyObjects
	{
		Trigger *stair;
		Door *door;
	};
}