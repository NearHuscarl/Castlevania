#pragma once

#include <Windows.h>
#include <vector>
#include "AnimationFrame.h"

class Animation
{
public:
	Animation(int defaultTime);
	void Add(int spriteId, DWORD time = 0);
	void Render(float x, float y);

private:
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	std::vector<AnimationFrame*> frames;
};
