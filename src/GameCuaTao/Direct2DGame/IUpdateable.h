#pragma once

#include "GameTime.h"

class IUpdateable
{
public:
	virtual void Update(GameTime gameTime) = 0;
};