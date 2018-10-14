#pragma once

#include "Sprite.h"

class AnimationFrame
{
public:
	AnimationFrame();
	AnimationFrame(Sprite sprite, unsigned long time);
	unsigned long GetTime();
	Sprite &GetSprite();

private:
	Sprite sprite;
	unsigned long time;
};