#include "SpriteFont.h"

SpriteFont::SpriteFont()
{
	this->font = nullptr;
}

SpriteFont::SpriteFont(Font_ font)
{
	this->font = font;
}

Font_ SpriteFont::Get()
{
	return font;
}

void SpriteFont::Draw(ISpriteBatch_ spriteBatch, std::string text, Vector position, Color fgcolor)
{
	if (font == nullptr)
		return;

	auto boundingBox = BoundingBox(position.x, position.y, 2000, 2000); // TODO: remove const with window width and height

	font->DrawTextA(spriteBatch, text.c_str(), -1, &boundingBox, DT_LEFT, fgcolor.Get());
}

