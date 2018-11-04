#include "AnimationSet.h"

AnimationSet::AnimationSet(std::map<std::string, Animation> animations)
{
	for (auto const&[name, animation] : animations)
	{
		this->animations.emplace(name, animation);
	}
}

Animation &AnimationSet::GetCurrentAnimation()
{
	return currentAnimation;
}

void AnimationSet::Play(std::string animation)
{
	if (currentAnimation.GetName() != animation || currentAnimation.IsComplete())
	{
		currentAnimation = animations.at(animation);
	}
}

void AnimationSet::Update(float deltaTime)
{
	if (!currentAnimation.IsComplete())
	{
		currentAnimation.Update();
	}
}