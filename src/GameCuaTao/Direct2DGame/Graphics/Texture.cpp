#include "Texture.h"

Texture::Texture() noexcept
{
	this->texture = nullptr;
}

Texture::Texture(ITexture_ texture, ImageInfo info) noexcept
{
	this->texture = texture;
	this->info = info;
}

Texture::Texture(Texture &&rhs) noexcept : texture{ rhs.texture }
{
	rhs.texture = nullptr;
}

Texture &Texture::operator=(Texture &&rhs) noexcept
{
	texture = rhs.texture;
	rhs.texture = nullptr;
	return *this;
}

ITexture_ Texture::Get() const noexcept
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

Texture::~Texture() noexcept
{
	if (texture != nullptr)
	{
		texture->Release();
		texture = nullptr;
	}
}