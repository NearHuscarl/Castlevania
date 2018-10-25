#include "SpriteFont.h"
#include "../Base/BoundingBox.h"

SpriteFont::SpriteFont(IFont_ font)
{
	this->font = font;
}

IFont_ SpriteFont::Get()
{
	return font;
}

Vector SpriteFont::MessureString(std::string text)
{
	if (font == nullptr)
	{
		return Vector(0, 0);
	}

	auto rectangle = BoundingBox{ 0,0,0,0 };
	auto str = text.c_str();

	// calculate required rect
	font->DrawTextA(nullptr, str, strlen(str), &rectangle, DT_CALCRECT, D3DCOLOR_XRGB(0, 0, 0));

	return Vector(rectangle.right - rectangle.left, rectangle.bottom - rectangle.top);
}