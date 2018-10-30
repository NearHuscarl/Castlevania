#pragma once

#include <string>
#include "../Graphics/SpriteBatch.h"

class Sprite
{
public:
	Sprite();
	Sprite(std::string spriteID, Rect spriteFrame);
	Sprite(std::string spriteID, Rect spriteFrame, Rect spriteBoundary);

	Rect GetSpriteFrame();
	Rect GetSpriteBoundary();

	void Draw(SpriteBatch &spriteBatch, Texture &texture, Vector2 position, Color color, SpriteEffects effects);

private:
	std::string id;
	Rect spriteFrame; // used to draw
	Rect spriteBoundary; // used to detect collision
};