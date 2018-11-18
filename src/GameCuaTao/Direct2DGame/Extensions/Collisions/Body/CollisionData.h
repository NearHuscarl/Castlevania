#pragma once

#include "CollisionResult.h"
#include "../../../Base/Vector2.h"

struct CollisionData
{
	CollisionResults collisionResults;
	Vector2 minTime = Vector2{ -1, -1 };
	Vector2 minNormal = Vector2::Zero();
};
