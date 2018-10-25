#pragma once

#include "string"
#include "../Device.h"
#include "../Base/Vector.h"

class SpriteFont
{
public:
	SpriteFont(IFont_ font);

	IFont_ Get();
	Vector MessureString(std::string text);

private:
	IFont_ font;
};