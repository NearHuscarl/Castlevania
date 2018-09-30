#pragma once

#include <unordered_map>
#include "Animation.h"

class AnimationManager
{
public:
	void Add(int id, Animation *ani);
	Animation *Get(int id);

	static AnimationManager *GetInstance();

private:
	static AnimationManager *instance;

	std::unordered_map<int, Animation*> animations;
};
