#include "SpriteExtensions.h"
#include "Direct2DGame/MathHelper.h"

SpriteExtensions::SpriteExtensions(GraphicsDevice &graphicsDevice) : SpriteBatch(graphicsDevice)
{
}

void SpriteExtensions::Draw(Sprite sprite, Vector2 position, bool useViewport)
{
	Draw(sprite, position, 0.0f, Vector2::One(), useViewport);
}

void SpriteExtensions::Draw(Sprite sprite, Transform transform, bool useViewport)
{
	Draw(sprite, transform.position, transform.rotation, transform.scale, useViewport);
}

void SpriteExtensions::Draw(Sprite sprite, Vector2 position, float rotation, Vector2 scale, bool useViewport)
{
	if (sprite.IsVisible())
	{
		auto &texture = sprite.GetTextureRegion().GetTexture();
		auto spriteFrame = sprite.GetTextureRegion().GetFrameRectangle();
		auto color = sprite.GetColor() * sprite.GetAlpha();
		auto effects = sprite.GetEffect();

		if (useViewport)
		{
			auto viewportRect = graphicsDevice.GetViewport().Bounds();
			auto spriteRect = sprite.GetFrameRectangle(position);

			if (!viewportRect.TouchesOrIntersects(spriteRect)) // Dont draw if object is outside of viewport
				return;
		}

		Draw(texture, position, &spriteFrame, color, rotation, scale, effects, useViewport);
	}
}
