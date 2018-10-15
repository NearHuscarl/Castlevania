#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::Sprite(std::string spriteID, BoundingBox boundingBox)
{
	this->id = spriteID;
	this->boundingBox = boundingBox;
}

void Sprite::Draw(SpritePtr spriteHandler, Texture texture, Vector position)
{
	spriteHandler->Draw(texture, &boundingBox, nullptr, &position, D3DCOLOR_XRGB(255, 255, 255));
}