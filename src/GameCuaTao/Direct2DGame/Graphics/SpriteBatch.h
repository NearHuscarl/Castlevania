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

	GraphicsDevice &GetGraphicsDevice();

	void Begin(unsigned long flags);
	void End();

	void Draw(Texture &texture, Vector2 position, Color color);
	void Draw(Texture &texture, Vector2 position, Rect *rectangle, Color color, float rotation, Vector2 scale, SpriteEffects effects);
	void DrawString(SpriteFont &spriteFont, std::string text, Vector2 position, Color color);

protected:
	GraphicsDevice &graphicsDevice;

private:
	ISpriteHandler_ spriteHandler;
};
