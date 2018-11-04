#pragma once

#include <map>
#include "Direct2DGame/Animations/Animation.h"

class AnimationSet
{
public:
	AnimationSet(std::map<std::string, Animation> animations);
	Animation &GetCurrentAnimation();

	void Play(std::string animation);
	void Update(float deltaTime);

private:
	std::map<std::string, Animation> animations;
	Animation currentAnimation;
};