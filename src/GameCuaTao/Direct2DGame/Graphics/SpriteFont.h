#pragma once

#include "string"
#include "../Device.h"
#include "../Base/Vector2.h"

class SpriteFont
{
public:
	SpriteFont(IFont_ font);

	IFont_ Get();
	Vector2 MessureString(std::string text);

private:
	IFont_ font;
};