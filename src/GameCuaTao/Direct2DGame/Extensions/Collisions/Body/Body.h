#pragma once

#include "CollisionData.h"

class Body
{
public:
	Body(IColliable &colliableObject);

	CollisionData GetCollisionData();
	void SetCollisionData(CollisionData collisionData);

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
	CollisionData collisionData;

	SweptAABBResult SweptAABB(RectF movingRect, Vector2 distance, RectF staticRect);
	BroadPhase CreateBroadPhase(RectF rect, Vector2 distance);
};
