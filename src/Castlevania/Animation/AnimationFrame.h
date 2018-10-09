#pragma once

#include "Sprite.h"

class AnimationFrame
{
public:
	AnimationFrame(Sprite *sprite, unsigned long time);
	unsigned long GetTime() { return time; }
	Sprite *GetSprite() { return sprite; }

private:
	Sprite *sprite;
	unsigned long time;
};