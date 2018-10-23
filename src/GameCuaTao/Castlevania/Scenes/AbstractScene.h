#pragma once

#include "Direct2DGame/Graphics/SpriteBatch.h"
#include "Direct2DGame/Content/ContentManager.h"

class AbstractScene
{
public:
	virtual void LoadContent(ContentManager &content) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Draw(SpriteBatch &spriteBatch) = 0;
};