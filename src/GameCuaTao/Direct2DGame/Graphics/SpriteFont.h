#pragma once

#include "string"
#include "../Device.h"
#include "../Base/BoundingBox.h"
#include "../Base/Color.h"
#include "../Base/Vector.h"

class SpriteFont
{
public:
	SpriteFont();
	SpriteFont(IFont_ font);

	IFont_ Get();
	void Draw(ISpriteBatch_ spriteBatch, std::string text, Vector position, Color fgcolor);

private:
	IFont_ font;
};