#pragma once

#include "../IGameObject.h"
#include "CollisionResult.h"
#include "Direction.h"

namespace Castlevania
{
	class Body
	{
	public:
		Body(IGameObject &dynamicObject);

		void Update(float deltaTime);
		CollisionResult PredictCollision(IGameObject &dynamicObject);
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

		float deltaTime; // in milliseconds
		IGameObject &parent;

		SweptAABBResult SweptAABB(RectF movingRect, Vector2 distance, RectF staticRect);
		BroadPhase CreateBroadPhase(RectF rect, Vector2 distance);
	};
}