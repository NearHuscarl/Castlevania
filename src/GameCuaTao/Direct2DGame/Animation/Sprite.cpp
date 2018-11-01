#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::Sprite(std::string spriteID, Rect spriteFrame)
{
	this->id = spriteID;
	this->spriteFrame = spriteFrame;
	this->spriteBoundary = spriteFrame;
}

Sprite::Sprite(std::string spriteID, Rect spriteFrame, Rect spriteBoundary)
{
	this->id = spriteID;
	this->spriteFrame = spriteFrame;
	this->spriteBoundary = spriteBoundary;
}

std::string Sprite::GetID()
{
	return id;
}

Rect Sprite::GetSpriteFrame()
{
	return spriteFrame;
}

Rect Sprite::GetSpriteBoundary()
{
	return spriteBoundary;
}

void Sprite::Draw(SpriteBatch &spriteBatch, Texture &texture, Vector2 position, Color color, SpriteEffects effects)
{
	spriteBatch.Draw(texture, position, &spriteFrame, color, effects);
}