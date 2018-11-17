#pragma once

#include <memory>
#include "../Graphics/Texture.h"
#include "../Base/Rect.h"
#include "RectF.h"

class TextureRegion
{
public:
	TextureRegion(std::shared_ptr<Texture> texture);
	TextureRegion(std::shared_ptr<Texture> texture, Rect frame);
	TextureRegion(std::shared_ptr<Texture> texture, Rect frame, RectF boundary);

	Texture &GetTexture();
	Rect GetFrameRectangle();
	RectF GetBoundingRectangle();

private:
	std::shared_ptr<Texture> texture;
	Rect frame; // used to draw
	RectF boundary; // used to detect collision
};