#include "SpriteExtensions.h"

SpriteExtensions::SpriteExtensions(GraphicsDevice &graphicsDevice) : SpriteBatch(graphicsDevice)
{
}

void SpriteExtensions::Draw(Sprite sprite, Transform transform)
{
	if (sprite.IsVisible())
	{
		auto position = transform.position;
		auto rotation = transform.rotation;
		auto scale = transform.scale;

		auto &texture = sprite.GetTextureRegion().GetTexture();
		auto spriteFrame = sprite.GetTextureRegion().GetFrameRectangle();
		auto color = sprite.GetColor() * sprite.GetAlpha();
		auto effect = sprite.GetEffect();

		Draw(texture, position, &spriteFrame, color, rotation, scale, effect);
	}
}
