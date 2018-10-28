#include "SpriteFont.h"
#include "../Base/Rect.h"

SpriteFont::SpriteFont(IFont_ font)
{
	this->font = font;
}

IFont_ SpriteFont::Get()
{
	return font;
}

Vector2 SpriteFont::MessureString(std::string text)
{
	if (font == nullptr)
	{
		return Vector2(0, 0);
	}

	auto rect = Rect{};
	auto str = text.c_str();

	// calculate required rect
	font->DrawTextA(nullptr, str, strlen(str), &rect, DT_CALCRECT, D3DCOLOR_XRGB(0, 0, 0));

	auto width = (float)(rect.right - rect.left);
	auto height = (float)(rect.bottom - rect.top);

	return Vector2(width, height);
}