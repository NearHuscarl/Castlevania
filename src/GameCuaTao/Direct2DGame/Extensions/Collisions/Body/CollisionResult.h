#pragma once

#include <vector>
#include "../IColliable.h"
#include "../../Direction.h"

struct CollisionResult
{
	float timeToCollide;
	Direction direction;
	IColliable &collidedObject;

	CollisionResult(float timeToCollide, Direction direction, IColliable &collidedObject) : collidedObject{ collidedObject }
	{
		this->timeToCollide = timeToCollide;
		this->direction = direction;
	}

	bool ShouldCollide()
	{
		return 0 < timeToCollide && timeToCollide <= 1;
	}
};

using CollisionResults = std::vector<CollisionResult>;
