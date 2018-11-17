#include "TextureRegion.h"

TextureRegion::TextureRegion(std::shared_ptr<Texture> texture)
	: TextureRegion(texture, Rect(0, 0, texture->Width(), texture->Height()))
{
}

TextureRegion::TextureRegion(std::shared_ptr<Texture> texture, Rect frame)
{
	this->texture = texture;
	this->frame = frame;
	this->boundary = (RectF)frame;
}

TextureRegion::TextureRegion(std::shared_ptr<Texture> texture, Rect frame, RectF boundary)
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

RectF TextureRegion::GetBoundingRectangle()
{
	return boundary;
}
