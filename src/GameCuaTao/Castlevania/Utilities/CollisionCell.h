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
		UGameObjects &GetEntites();

		void AddBlock(std::shared_ptr<GameObject> object);
		void AddEntity(std::unique_ptr<GameObject> object);
		void AddStaticObject(std::unique_ptr<GameObject> object);

	private:
		CollisionObject collisionObject;
		RectF boundingBox;

		void AddObject(UGameObjects &objects, std::unique_ptr<GameObject> newObject);
		void AddSharedObject(SGameObjects &objects, std::shared_ptr<GameObject> newObject);
	};
}