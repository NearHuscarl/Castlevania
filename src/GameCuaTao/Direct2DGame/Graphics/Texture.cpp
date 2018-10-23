#include "Texture.h"

Texture::Texture(ITexture_ texture, ImageInfo info)
{
	this->texture = texture;
	this->info = info;
}

ITexture_ Texture::Get()
{
	return texture;
}

int Texture::Width()
{
	return info.Width;
}

int Texture::Height()
{
	return info.Height;
}

ImageInfo &Texture::GetInfo()
{
	return info;
}
