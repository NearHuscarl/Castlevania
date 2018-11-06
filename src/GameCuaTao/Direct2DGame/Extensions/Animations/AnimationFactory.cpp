#include "AnimationFactory.h"

AnimationFactory::AnimationFactory(AnimationDict animations)
{
	for (auto const&[name, animation] : animations)
	{
		this->animations.emplace(name, animation);
	}
}

Animation *AnimationFactory::Create()
{
	return &animations.begin()->second;
}

Animation *AnimationFactory::Create(std::string name)
{
	return &animations.at(name);
}