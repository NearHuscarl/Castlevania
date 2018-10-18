#include "Texture.h"

Texture::Texture(ITexture_ texture)
{
	this->texture = texture;
}

ITexture_ Texture::Get()
{
	return texture;
}