#pragma once

#include "CollisionResult.h"
#include "Direction.h"

class Body
{
public:
	Body(IColliable &colliableObject);

	CollisionResult PredictCollision(IColliable &staticObject);

private:
	struct SweptAABBResult
	{
		float timeToCollide;
		Direction direction;

		static SweptAABBResult Empty()
		{
			return SweptAABBResult{ -1, Direction::None };
		}
	};

	using BroadPhase = RectF;

	IColliable &parent;

	SweptAABBResult SweptAABB(RectF movingRect, Vector2 distance, RectF staticRect);
	BroadPhase CreateBroadPhase(RectF rect, Vector2 distance);
};
