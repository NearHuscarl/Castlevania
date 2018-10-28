#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::Sprite(std::string spriteID, Rect rect)
{
	this->id = spriteID;
	this->rect = rect;
}

void Sprite::Draw(SpriteBatch &spriteBatch, Texture &texture, Vector2 position, Color color, SpriteEffects effects)
{
	spriteBatch.Draw(texture, position, &rect, color, effects);
}