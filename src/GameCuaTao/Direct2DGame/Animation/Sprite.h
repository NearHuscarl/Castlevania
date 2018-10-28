#pragma once

#include <string>
#include "../Graphics/SpriteBatch.h"

class Sprite
{
public:
	Sprite();
	Sprite(std::string spriteID, Rect rect);

	void Draw(SpriteBatch &spriteBatch, Texture &texture, Vector2 position, Color color, SpriteEffects effects);

private:
	std::string id;
	Rect rect;
};