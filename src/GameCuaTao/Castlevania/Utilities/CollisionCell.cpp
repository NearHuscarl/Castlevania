#include "CollisionCell.h"

using namespace Castlevania;

CollisionCell::CollisionCell(RectF boundingBox)
{
	this->boundingBox = boundingBox;
}

CollisionCell &CollisionCell::NullCell()
{
	static auto nullCell = CollisionCell{ RectF::Empty() };
	return nullCell;
}

void CollisionCell::AddEntity(std::unique_ptr<GameObject> object)
{
	AddObject(collisionObject.entities, std::move(object));
}

void CollisionCell::AddStaticObject(std::unique_ptr<GameObject> object)
{
	AddObject(collisionObject.staticObjects, std::move(object));
}

void CollisionCell::AddObject(GameObjects &objects, std::unique_ptr<GameObject> newObject)
{
	auto newUnit = objects.insert(objects.end(), std::move(newObject));
	objects.back()->SetCollisionGridData(CollisionGridData{ false, 0, 0, 0, 0, newUnit });
}

RectF CollisionCell::GetBoundingBox()
{
	return boundingBox;
}

CollisionObject &CollisionCell::GetObjects()
{
	return collisionObject;
}

GameObjects &CollisionCell::GetStaticObjects()
{
	return collisionObject.staticObjects;
}

GameObjects &CollisionCell::GetEntites()
{
	return collisionObject.entities;
}
