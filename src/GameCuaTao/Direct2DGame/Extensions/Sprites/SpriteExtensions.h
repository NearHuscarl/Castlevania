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
	void Draw(Sprite sprite, Vector2 position, float rotation = 0.0f, Vector2 scale = Vector2::One());
	void Draw(RectF rect, Color color);

private:
	ISurface_ plainSurface;
};