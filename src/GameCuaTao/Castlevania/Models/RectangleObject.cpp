#include "RectangleObject.h"

using namespace Castlevania;

RectangleObject::RectangleObject(RectF rect) : GameObject(EntityType::Boundary)
{
	this->boundingBox = rect;
}

RectF RectangleObject::GetBoundingBox()
{
	return boundingBox;
}

RectangleObject::~RectangleObject()
{
}
