#include "SpriteFont.h"

SpriteFont::SpriteFont(IFont_ font)
{
	this->font = font;
}

IFont_ SpriteFont::Get()
{
	return font;
}