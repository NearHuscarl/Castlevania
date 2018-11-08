#include "SpriteExtensions.h"

SpriteExtensions::SpriteExtensions(GraphicsDevice &graphicsDevice) : SpriteBatch(graphicsDevice)
{
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
		auto effect = sprite.GetEffect();

		Draw(texture, position, &spriteFrame, color, rotation, scale, effect);
	}
}
