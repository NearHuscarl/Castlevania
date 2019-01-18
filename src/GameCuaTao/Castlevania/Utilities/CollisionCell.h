#pragma once

#include "CollisionObject.h"

namespace Castlevania
{
	class CollisionCell
	{
	public:
		CollisionCell(RectF boundingBox);

		static CollisionCell &NullCell();

		RectF GetBoundingBox();
		CollisionObject &GetObjects();
		GameObjects &GetStaticObjects();
		GameObjects &GetEntites();

		void AddEntity(std::unique_ptr<GameObject> object);
		void AddStaticObject(std::unique_ptr<GameObject> object);

	private:
		CollisionObject collisionObject;
		RectF boundingBox;

		void AddObject(GameObjects &objects, std::unique_ptr<GameObject> newObject);
	};
}