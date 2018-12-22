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

void CollisionCell::AddBlock(std::shared_ptr<GameObject> object)
{
	AddSharedObject(collisionObject.blocks, object);
}

void CollisionCell::AddEntity(std::unique_ptr<GameObject> object)
{
	AddObject(collisionObject.entities, std::move(object));
}

void CollisionCell::AddStaticObject(std::unique_ptr<GameObject> object)
{
	AddObject(collisionObject.staticObjects, std::move(object));
}

void CollisionCell::AddObject(UGameObjects &objects, std::unique_ptr<GameObject> newObject)
{
	auto newUnit = objects.insert(objects.end(), std::move(newObject));
	objects.back()->SetCollisionUnit(newUnit);
}

void CollisionCell::AddSharedObject(SGameObjects &objects, std::shared_ptr<GameObject> newObject)
{
	// shared object in this case is static objects 
	// which do not need unit to move between cells
	objects.push_back(newObject);
}

RectF CollisionCell::GetBoundingBox()
{
	return boundingBox;
}

CollisionObject &CollisionCell::GetObjects()
{
	return collisionObject;
}

UGameObjects &CollisionCell::GetEntites()
{
	return collisionObject.entities;
}
