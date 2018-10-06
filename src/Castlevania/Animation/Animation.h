#pragma once

#include <vector>
#include "AnimationFrame.h"


class Animation
{
public:
	Animation(int defaultTime);
	void Add(std::string spriteId, DWORD time = 0);
	void Update();
	void Render(float x, float y);

private:
	DWORD lastFrameTime;
	int defaultTime;
	int currentFrame;
	std::vector<AnimationFrame*> frames;
};
