#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(std::shared_ptr<AnimationFactory> animationFactory) :
	Sprite{ animationFactory->Create()->GetCurrentFrame().GetTextureRegion() }
{
	this->animationFactory = animationFactory;
	this->currentAnimation = animationFactory->Create();
}

AnimatedSprite::AnimatedSprite(std::shared_ptr<AnimationFactory> animationFactory, std::vector<std::string> animations) :
	Sprite{ animationFactory->Create()->GetCurrentFrame().GetTextureRegion() }
{
	this->animationFactory = animationFactory->CreateAnimationFactory(animations);
	this->currentAnimation = animationFactory->Create();
}

Animation &AnimatedSprite::GetCurrentAnimation()
{
	return *currentAnimation;
}

bool AnimatedSprite::AnimateComplete()
{
	return currentAnimation->IsComplete();
}

void AnimatedSprite::Play(std::string name)
{
	if (currentAnimation->GetName() != name || currentAnimation->IsComplete())
	{
		currentAnimation = animationFactory->Create(name);
	}
}

void AnimatedSprite::Update()
{
	if (!currentAnimation->IsComplete())
	{
		currentAnimation->Update();
		SetTextureRegion(currentAnimation->GetCurrentFrame().GetTextureRegion());
	}
}