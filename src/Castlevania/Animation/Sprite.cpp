#include "Sprite.h"

Graphics *Sprite::graphics;


void Sprite::Initialize(Graphics *graphics)
{
	Sprite::graphics = graphics;
}

Sprite::Sprite(std::string id, BoundingBox boundingBox, GTexturePtr texture)
{
	this->id = id;
	this->boundingBox = boundingBox;
	this->texture = texture;
}

void Sprite::Draw(float x, float y)
{
	D3DXVECTOR3 p(x, y, 0);
	GSpritePtr spriteHandler = graphics->GetSpriteHandler();

	spriteHandler->Draw(texture, &boundingBox, NULL, &p, D3DCOLOR_XRGB(255, 255, 255));
}