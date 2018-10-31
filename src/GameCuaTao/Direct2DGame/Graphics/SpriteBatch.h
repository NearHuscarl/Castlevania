#pragma once

#include "../Graphics/GraphicsDevice.h"
#include "../Graphics/SpriteFont.h"
#include "../Graphics/SpriteEffects.h"
#include "../Graphics/Texture.h"

// An extension to DirectX sprite handler ID3DXSprite
class SpriteBatch
{
public:
	SpriteBatch(GraphicsDevice &graphicsDevice);
	ISpriteHandler_ GetSpriteHandler();
	
	void Draw(Texture &texture, Vector2 position, Rect *rectangle, Color color, SpriteEffects effects = SpriteEffects::None);
	void DrawString(SpriteFont &spriteFont, std::string text, Vector2 position, Color color);

private:
	ISpriteHandler_ spriteHandler;
};