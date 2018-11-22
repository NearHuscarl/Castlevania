#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(std::shared_ptr<AnimationFactory> animationFactory) :
	Sprite{ animationFactory->Create().GetCurrentFrame().GetTextureRegion() },
	currentAnimation{ animationFactory->Create() }
{
	this->animationFactory = animationFactory;
}

AnimatedSprite::AnimatedSprite(std::shared_ptr<AnimationFactory> animationFactory, std::vector<std::string> animations) :
	Sprite{ animationFactory->Create().GetCurrentFrame().GetTextureRegion() },
	currentAnimation{ animationFactory->Create() }
{
	this->animationFactory = animationFactory->CreateAnimationFactory(animations);
}

Animation &AnimatedSprite::GetCurrentAnimation()
{
	return currentAnimation;
}

bool AnimatedSprite::AnimateComplete()
{
	return currentAnimation.IsComplete();
}

void AnimatedSprite::Play(std::string name)
{
	if (currentAnimation.GetName() != name || currentAnimation.IsComplete())
	{
		if (name == "")
			currentAnimation = animationFactory->Create(); // Play the default animation
		else
			currentAnimation = animationFactory->Create(name);
	}
}

void AnimatedSprite::Update()
{
	if (!currentAnimation.IsComplete())
	{
		currentAnimation.Update();
		SetTextureRegion(currentAnimation.GetCurrentFrame().GetTextureRegion());
	}
}