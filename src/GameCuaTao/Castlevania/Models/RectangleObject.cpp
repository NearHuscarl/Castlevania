#include "RectangleObject.h"

using namespace Castlevania;

RectangleObject::RectangleObject(RectF rect, EntityType type) : body{ *this }
{
	this->identifier = type;
	this->boundingBox = rect;
}

int RectangleObject::GetType()
{
	return (int)identifier;
}

Vector2 RectangleObject::GetDistance()
{
	return Vector2::Zero();
}

RectF RectangleObject::GetBoundingBox()
{
	return boundingBox;
}

Vector2 RectangleObject::Center()
{
	return Vector2{
		boundingBox.left + boundingBox.Width() / 2,
		boundingBox.top + boundingBox.Height() / 2 };
}

Facing RectangleObject::GetFacing()
{
	return facing;
}

void RectangleObject::SetFacing(Facing facing)
{
	this->facing = facing;
}

Body &RectangleObject::GetBody()
{
	return body;
}
