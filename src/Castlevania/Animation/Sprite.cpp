#include "Sprite.h"

Sprite::Sprite(std::string spriteID, BoundingBox boundingBox, IDirect3DTexture9 *texture)
{
	this->id = spriteID;
	this->boundingBox = boundingBox;
	this->texture = texture;
}

void Sprite::Draw(ID3DXSprite *spriteHandler, float x, float y)
{
	D3DXVECTOR3 p(x, y, 0);
	spriteHandler->Draw(texture, &boundingBox, nullptr, &p, D3DCOLOR_XRGB(255, 255, 255));
}