#pragma once

#include "SpriteExtensions.h"

class IDrawable
{
public:
	virtual void Draw(SpriteExtensions &spriteBatch) = 0;
	virtual ~IDrawable() {}
};