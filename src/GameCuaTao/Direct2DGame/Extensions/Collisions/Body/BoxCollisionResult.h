#pragma once

#include <vector>
#include "../../RectF.h"
#include "../../Direction.h"

struct BoxCollisionResult
{
	float timeToCollide;
	Direction direction;
	RectF boundingBox;

	BoxCollisionResult(float timeToCollide, Direction direction, RectF boundingBox)
	{
		this->timeToCollide = timeToCollide;
		this->direction = direction;
		this->boundingBox = boundingBox;
	}

	bool ShouldCollide()
	{
		return 0 < timeToCollide && timeToCollide <= 1;
	}
};

using BoxCollisionResults = std::vector<BoxCollisionResult>;
