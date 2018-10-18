#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::Sprite(std::string spriteID, BoundingBox boundingBox)
{
	this->id = spriteID;
	this->boundingBox = boundingBox;
}

void Sprite::Draw(ISpriteBatch_ spriteBatch, Texture texture, Vector position, SpriteEffects effects)
{
	D3DXMATRIX oldMatrix;
	spriteBatch->GetTransform(&oldMatrix);

	D3DXVECTOR2 rotate;
	if (effects == FlipHorizontally)
		rotate = D3DXVECTOR2(-1, 1);
	else if (effects == FlipVertically)
		rotate = D3DXVECTOR2(1, -1);
	else // None
		rotate = D3DXVECTOR2(1, 1);

	D3DXVECTOR2 center = D3DXVECTOR2(position.x + boundingBox.Width() / 2, position.y + boundingBox.Height() / 2);

	D3DXMATRIX newMatrix;
	D3DXMatrixTransformation2D(&newMatrix, &center, 0.0f, &rotate, nullptr, 0.0f, nullptr);
	D3DXMATRIX finalMatrix = oldMatrix * newMatrix;
	
	spriteBatch->SetTransform(&finalMatrix);
	spriteBatch->Draw(texture.Get(), &boundingBox, nullptr, &position, D3DCOLOR_XRGB(255, 255, 255));
	spriteBatch->SetTransform(&oldMatrix);
}