#pragma once

#include <vector>
#include "AnimationFrame.h"
#include "../TextureRegion.h"

class Animation
{
public:
	Animation(std::string name, int defaultTime = 100, bool isLooping = true);

	std::string GetName();
	AnimationFrame GetCurrentFrame();

	bool IsComplete();

	void Add(TextureRegion textureRegion, int time = 0);
	void Update();
	void Reset();

private:
	bool isLooping;
	bool isComplete;

	int lastFrameTime;
	int defaultTime;
	int currentFrame;

	std::string name;
	std::vector<AnimationFrame> frames;
};
