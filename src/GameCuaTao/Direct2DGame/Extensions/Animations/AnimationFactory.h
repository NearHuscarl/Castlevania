#pragma once

#include <map>
#include <string>
#include "Animation.h"

using AnimationDict = std::map<std::string, Animation>;

class AnimationFactory
{
public:
	AnimationFactory(AnimationDict animations);
	
	Animation *Create(); // Return the default (first) animation
	Animation *Create(std::string name);

	// Create a new animation factory from a subset animation of this factory
	std::shared_ptr<AnimationFactory> CreateAnimationFactory(std::vector<std::string> animationNames);

private:
	AnimationDict animations;
};