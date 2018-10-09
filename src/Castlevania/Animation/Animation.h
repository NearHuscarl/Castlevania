#pragma once

#include <vector>
#include "AnimationFrame.h"

class Animation
{
public:
	Animation(unsigned long defaultTime = 100);
	void Add(Sprite *sprite, unsigned long time = 0);
	void Update();
	void Draw(ID3DXSprite *spriteHandler, float x, float y);

private:
	unsigned long lastFrameTime;
	unsigned long defaultTime;
	int currentFrame;
	std::vector<AnimationFrame*> frames;
};
