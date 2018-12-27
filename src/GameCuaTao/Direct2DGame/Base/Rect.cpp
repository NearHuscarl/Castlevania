#include "Rect.h"
#include "../Extensions/RectF.h"
#include "../MathHelper.h"

Rect::Rect() : Rect(0, 0, 0, 0)
{
}

Rect::Rect(int left, int top, int width, int height)
{
	this->left = left;
	this->top = top;
	this->right = left + width;
	this->bottom = top + height;
}

int Rect::X()
{
	return left;
}

int Rect::Y()
{
	return top;
}

int Rect::Width()
{
	return right - left;
}

int Rect::Height()
{
	return bottom - top;
}

Point Rect::Center()
{
	return Point{ X() + Width() / 2, Y() + Height() / 2 };
}

Rect Rect::Empty()
{
	static auto emptyRectangle = Rect{};
	return emptyRectangle;
}

bool Rect::operator==(Rect other)
{
	return (
		this->X() == other.X() &&
		this->Y() == other.Y() &&
		this->Width() == other.Width() &&
		this->Height() == other.Height());
}

bool Rect::operator!=(Rect other)
{
	return !(*this == other);
}

bool Rect::Contains(Rect value)
{
	return (
		this->left <= value.left &&
		this->top <= value.top &&
		this->right >= value.right &&
		this->bottom >= value.bottom);
}

bool Rect::Contains(Vector2 value)
{
	return (
		this->left <= value.x &&
		this->top <= value.y &&
		this->right >= value.x &&
		this->bottom >= value.y);
}

bool Rect::Intersects(Rect value)
{
	return (
		this->left < value.right &&
		this->top < value.bottom &&
		this->right > value.left &&
		this->bottom > value.top);
}

bool Rect::TouchesOrIntersects(Rect value)
{
	return (
		this->left <= value.right &&
		this->top <= value.bottom &&
		this->right >= value.left &&
		this->bottom >= value.top);
}

Rect Rect::Merge(Rect value1, Rect value2)
{
	if (value1 == Rect::Empty())
		return value2;

	if (value2 == Rect::Empty())
		return value1;

	auto left = MathHelper::Min(value1.left, value2.left);
	auto top = MathHelper::Min(value1.top, value2.top);
	auto right = MathHelper::Max(value1.right, value2.right);
	auto bottom = MathHelper::Max(value1.bottom, value2.bottom);

	return Rect{ left, top, right - left, bottom - top };
}

Rect::operator RectF()
{
	return RectF{ (float)left, (float)top, (float)Width(), (float)Height() };
}
