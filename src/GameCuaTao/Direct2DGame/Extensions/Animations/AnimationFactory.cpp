#include "AnimationFactory.h"

AnimationFactory::AnimationFactory(AnimationDict animations)
{
	for (auto const&[name, animation] : animations)
	{
		this->animations.emplace(name, animation);
	}
}

Animation AnimationFactory::Create()
{
	return animations.begin()->second;
}

Animation AnimationFactory::Create(std::string name)
{
	return animations.at(name);
}

std::shared_ptr<AnimationFactory> AnimationFactory::CreateAnimationFactory(std::vector<std::string> animationNames)
{
	auto newAnimations = AnimationDict{};

	for (auto animationName : animationNames)
	{
		auto it = animations.find(animationName);

		if (it != animations.end())
			newAnimations.emplace(animationName, animations.at(animationName));
	}

	return std::make_shared<AnimationFactory>(newAnimations);
}
