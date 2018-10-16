#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::Sprite(std::string spriteID, BoundingBox boundingBox)
{
	this->id = spriteID;
	this->boundingBox = boundingBox;
}

void Sprite::Draw(ISpriteHandler_ spriteHandler, Texture texture, Vector position)
{
	spriteHandler->Draw(texture.Get(), &boundingBox, nullptr, &position, D3DCOLOR_XRGB(255, 255, 255));
}