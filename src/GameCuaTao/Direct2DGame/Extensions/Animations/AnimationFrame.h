#pragma once

#include <memory>
#include "../TextureRegion.h"

class AnimationFrame
{
public:
	AnimationFrame(TextureRegion textureRegion, int time);

	TextureRegion GetTextureRegion();
	int GetTime();

private:
	TextureRegion textureRegion;
	int time;
};