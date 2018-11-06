#pragma once

#include <memory>
#include "../Graphics/Texture.h"
#include "../Base/Rect.h"

class TextureRegion
{
public:
	TextureRegion(std::shared_ptr<Texture> texture);
	TextureRegion(std::shared_ptr<Texture> texture, Rect frame);
	TextureRegion(std::shared_ptr<Texture> texture, Rect frame, Rect boundary);

	Texture &GetTexture();
	Rect GetFrameRectangle();
	Rect GetBoundingRectangle();

private:
	std::shared_ptr<Texture> texture;
	Rect frame; // used to draw
	Rect boundary; // used to detect collision
};