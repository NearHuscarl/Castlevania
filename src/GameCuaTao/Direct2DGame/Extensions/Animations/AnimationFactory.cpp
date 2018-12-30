#include "AnimationFactory.h"
#include "../../Utilities/CppExtensions.h"

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
	return GetValueOrDefault(animations, name, NULL_ANIMATION);
}

std::shared_ptr<AnimationFactory> AnimationFactory::Clone(std::vector<std::string> animationNames)
{
	auto newAnimations = AnimationDict{};

	for (auto animationName : animationNames)
	{
		auto it = animations.find(animationName);

		if (it != animations.end())
			newAnimations.emplace(animationName, animations.at(animationName));
	}

	return std::make_unique<AnimationFactory>(newAnimations);
}

AnimationDict AnimationFactory::GetAnimations()
{
	return animations;
}
