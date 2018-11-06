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

private:
	AnimationDict animations;
};