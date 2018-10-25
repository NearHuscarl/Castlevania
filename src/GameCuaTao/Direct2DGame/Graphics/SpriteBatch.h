#pragma once

#include "../Graphics/GraphicsDevice.h"
#include "../Base/BoundingBox.h"
#include "../Base/Color.h"
#include "../Base/Vector.h"
#include "../Graphics/SpriteFont.h"
#include "../Graphics/SpriteEffects.h"
#include "../Graphics/Texture.h"
#include "../Device.h"

// An extension to DirectX sprite handler ID3DXSprite
class SpriteBatch
{
public:
	SpriteBatch(GraphicsDevice &graphicsDevice);
	ISpriteHandler_ GetSpriteHandler();
	
	void Draw(Texture &texture, Vector position, BoundingBox *rectangle, Color color, SpriteEffects effects = SpriteEffects::None);
	void DrawString(SpriteFont &spriteFont, std::string text, Vector position, Color color);

private:
	ISpriteHandler_ spriteHandler;
};