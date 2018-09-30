#include "Sprite.h"
#include "../Animation/TextureManager.h"

Sprite::Sprite(int id, int left, int top, int right, int bottom, GTexturePtr texture)
{
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = texture;
}

void Sprite::Draw(float x, float y)
{
	TextureManager *textureManager = TextureManager::GetInstance();
	textureManager->Draw(x, y, texture, left, top, right, bottom);
}