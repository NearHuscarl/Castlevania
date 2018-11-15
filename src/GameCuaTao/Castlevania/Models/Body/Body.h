#pragma once

#include "../IDynamic.h"
#include "CollisionResult.h"
#include "Direction.h"

namespace Castlevania
{
	class Body
	{
	public:
		Body(IDynamic &dynamicObject);

		void Update(float deltaTime);
		CollisionResult PredictCollision(IDynamic &dynamicObject);
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

		using BroadPhase = Rect;

		float deltaTime; // in milliseconds
		IDynamic &parent;

		SweptAABBResult SweptAABB(Rect movingRect, Vector2 distance, Rect staticRect);
		BroadPhase CreateBroadPhase(Rect rect, Vector2 distance);
	};
}