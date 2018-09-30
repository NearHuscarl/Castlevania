#pragma once

#include "Sprite.h"

class AnimationFrame
{
public:
	AnimationFrame(Sprite *sprite, int time);
	DWORD GetTime() { return time; }
	Sprite *GetSprite() { return sprite; }

private:
	Sprite *sprite;
	DWORD time;
};