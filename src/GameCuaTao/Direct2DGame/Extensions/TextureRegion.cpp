#include "TextureRegion.h"

TextureRegion::TextureRegion(std::shared_ptr<Texture> texture)
	: TextureRegion(texture, Rect(0, 0, texture->Width(), texture->Height()))
{
}

TextureRegion::TextureRegion(std::shared_ptr<Texture> texture, Rect frame)
{
	this->texture = texture;
	this->frame = frame;
	this->boundary = frame;
}

TextureRegion::TextureRegion(std::shared_ptr<Texture> texture, Rect frame, Rect boundary)
{
	this->texture = texture;
	this->frame = frame;
	this->boundary = boundary;
}

Texture &TextureRegion::GetTexture()
{
	return *texture;
}

Rect TextureRegion::GetFrameRectangle()
{
	return frame;
}

Rect TextureRegion::GetBoundingRectangle()
{
	return boundary;
}
