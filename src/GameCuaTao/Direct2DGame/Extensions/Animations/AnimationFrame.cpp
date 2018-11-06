#include "AnimationFrame.h"

AnimationFrame::AnimationFrame(TextureRegion textureRegion, int time)
	: textureRegion{ textureRegion }
{
	this->time = time;
}

int AnimationFrame::GetTime()
{
	return time;
}

TextureRegion AnimationFrame::GetTextureRegion()
{
	return textureRegion;
}