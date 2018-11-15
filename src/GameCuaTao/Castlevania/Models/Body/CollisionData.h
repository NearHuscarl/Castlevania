#pragma once

#include "Direct2DGame/Base/Vector2.h"
#include "CollisionResult.h"

namespace Castlevania
{
	struct CollisionData
	{
		CollisionResults collisionResults;
		Vector2 minTime = Vector2{ -1, -1 };
		Vector2 minNormal = Vector2::Zero();
	};
}