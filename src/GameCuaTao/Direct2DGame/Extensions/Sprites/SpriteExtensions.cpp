#include "SpriteExtensions.h"
#include "Direct2DGame/MathHelper.h"

SpriteExtensions::SpriteExtensions(GraphicsDevice &graphicsDevice) : SpriteBatch(graphicsDevice)
{
}

void SpriteExtensions::Draw(TextureRegion textureRegion, Vector2 position, Color color, bool useViewport)
{
	Draw(textureRegion, position, color, 0.0f, Vector2::One(), SpriteEffects::None, useViewport);
}

void SpriteExtensions::Draw(TextureRegion textureRegion, Vector2 position, Color color, float rotation, Vector2 scale, SpriteEffects effects, bool useViewport)
{
	auto &texture = textureRegion.GetTexture();
	auto srcRect = textureRegion.GetFrameRectangle();

	Draw(texture, position, &srcRect, color, rotation, scale, effects, useViewport);
}

void SpriteExtensions::Draw(Sprite sprite, Transform transform)
{
	Draw(sprite, transform.position, transform.rotation, transform.scale);
}

void SpriteExtensions::Draw(Sprite sprite, Vector2 position, float rotation, Vector2 scale)
{
	if (sprite.IsVisible())
	{
		auto &texture = sprite.GetTextureRegion().GetTexture();
		auto spriteFrame = sprite.GetTextureRegion().GetFrameRectangle();
		auto color = sprite.GetColor() * sprite.GetAlpha();
		auto effects = sprite.GetEffect();

		Draw(texture, position, &spriteFrame, color, rotation, scale, effects);
	}
}
