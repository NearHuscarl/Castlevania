#pragma once

#include "GameTime.h"

class IDrawable
{
public:
	virtual void Draw(GameTime gameTime) = 0;
	virtual ~IDrawable() {}
};