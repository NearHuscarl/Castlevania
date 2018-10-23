#pragma once

#include "string"
#include "../Device.h"
#include "../Base/BoundingBox.h"
#include "../Base/Color.h"
#include "../Base/Vector.h"

class SpriteFont
{
public:
	SpriteFont(IFont_ font);
	IFont_ Get();

private:
	IFont_ font;
};