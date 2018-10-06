#pragma once

#include <map>
#include "Animation.h"

typedef std::map<std::string, Animation*> AnimationDict;

class AnimationManager
{
public:
	static AnimationManager *GetInstance();
	
	void LoadResource();
	void AddAnimation(std::string animationID, int animateTime, std::vector<std::string> sprites);
	Animation *GetAnimation(std::string animationID);

private:
	static AnimationManager *instance;
	AnimationDict animations;
};