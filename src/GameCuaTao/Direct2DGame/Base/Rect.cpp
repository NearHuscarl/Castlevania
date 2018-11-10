#include "Rect.h"

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

bool Rect::Contains(Rect value)
{
	return (
		this->left <= value.left &&
		this->right >= value.right &&
		this->top <= value.top &&
		this->bottom >= value.bottom);
}
