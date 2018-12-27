#include "RectF.h"
#include "../MathHelper.h"

RectF::RectF() : RectF(0, 0, 0, 0)
{
}

RectF::RectF(float left, float top, float width, float height)
{
	this->left = left;
	this->top = top;
	this->right = left + width;
	this->bottom = top + height;
}

float RectF::X()
{
	return left;
}

float RectF::Y()
{
	return top;
}

float RectF::Width()
{
	return right - left;
}

float RectF::Height()
{
	return bottom - top;
}

Vector2 RectF::GetPosition()
{
	return Vector2{ X(), Y() };
}

RectF RectF::Empty()
{
	static auto emptyRectFangle = RectF{};
	return emptyRectFangle;
}

bool RectF::operator==(RectF other)
{
	return (
		this->X() == other.X() &&
		this->Y() == other.Y() &&
		this->Width() == other.Width() &&
		this->Height() == other.Height());
}

bool RectF::operator!=(RectF other)
{
	return !(*this == other);
}

bool RectF::Contains(RectF value)
{
	return (
		this->left <= value.left &&
		this->top <= value.top &&
		this->right >= value.right &&
		this->bottom >= value.bottom);
}

bool RectF::Contains(Vector2 value)
{
	return (
		this->left <= value.x &&
		this->top <= value.y &&
		this->right >= value.x &&
		this->bottom >= value.y);
}

bool RectF::Intersects(RectF value)
{
	return (
		this->left < value.right &&
		this->top < value.bottom &&
		this->right > value.left &&
		this->bottom > value.top);
}

bool RectF::TouchesOrIntersects(RectF value)
{
	return (
		this->left <= value.right &&
		this->top <= value.bottom &&
		this->right >= value.left &&
		this->bottom >= value.top);
}

RectF RectF::Merge(RectF value1, RectF value2)
{
	if (value1 == RectF::Empty())
		return value2;

	if (value2 == RectF::Empty())
		return value1;

	auto left = MathHelper::Min(value1.left, value2.left);
	auto top = MathHelper::Min(value1.top, value2.top);
	auto right = MathHelper::Max(value1.right, value2.right);
	auto bottom = MathHelper::Max(value1.bottom, value2.bottom);

	return RectF{ left, top, right - left, bottom - top };
}

RectF::operator Rect()
{
	return Rect{ (int)left, (int)top, (int)Width(), (int)Height() };
}