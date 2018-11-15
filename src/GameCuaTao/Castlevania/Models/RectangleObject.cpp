#include "RectangleObject.h"

using namespace Castlevania;

RectangleObject::RectangleObject(Rect rect)
{
	boundingBox = rect;
}

EntityType RectangleObject::GetType()
{
	return type;
}

Vector2 RectangleObject::GetPosition()
{
	return position;
}

Rect RectangleObject::GetBoundingBox()
{
	return boundingBox;
}
