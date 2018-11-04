#pragma once

#include "Sprite.h"

class AnimationFrame
{
public:
	AnimationFrame();
	AnimationFrame(Sprite sprite, int time);

	int GetTime();
	Sprite &GetSprite();

private:
	Sprite sprite;
	int time;
};