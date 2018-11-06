#pragma once

#include "../../Graphics/SpriteBatch.h"
#include "../Sprites/Sprite.h"
#include "../Transform.h"

class SpriteExtensions : public SpriteBatch
{
public:
	SpriteExtensions(GraphicsDevice &graphicsDevice);

	using SpriteBatch::Draw;
	void Draw(Sprite sprite, Transform transform);
};