#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::Sprite(std::string spriteID, BoundingBox boundingBox)
{
	this->id = spriteID;
	this->boundingBox = boundingBox;
}

void Sprite::Draw(SpriteBatch &spriteBatch, Texture &texture, Vector2 position, Color color, SpriteEffects effects)
{
	spriteBatch.Draw(texture, position, &boundingBox, color, effects);
}