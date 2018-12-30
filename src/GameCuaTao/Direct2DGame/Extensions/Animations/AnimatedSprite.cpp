#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(std::shared_ptr<AnimationFactory> animationFactory) :
	Sprite{ animationFactory->Create().GetCurrentFrame().GetTextureRegion() }
{
	this->animationFactory = animationFactory;
	this->animations = this->animationFactory->GetAnimations();
	this->currentAnimation = &animations.begin()->second;
}

AnimatedSprite::AnimatedSprite(std::shared_ptr<AnimationFactory> animationFactory, std::vector<std::string> animations) :
	Sprite{ animationFactory->Create().GetCurrentFrame().GetTextureRegion() }
{
	this->animationFactory = animationFactory->Clone(animations);
	this->animations = this->animationFactory->GetAnimations();
	this->currentAnimation = &this->animations.begin()->second;
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
		auto newAnimation = animationFactory->Create(name);

		if (newAnimation.IsEmpty())
			return;

		currentAnimation->Stop();
		animations.at(name) = newAnimation;
		currentAnimation = &animations.at(name);

		SetTextureRegion(currentAnimation->GetCurrentFrame().GetTextureRegion());
	}
}

void AnimatedSprite::PlayCached(std::string name)
{
	if (currentAnimation->GetName() != name || currentAnimation->IsComplete())
	{
		auto it = animations.find(name);

		if (it == animations.end())
			return;

		currentAnimation->Stop();
		currentAnimation = &it->second;
		currentAnimation->Continue();

		SetTextureRegion(currentAnimation->GetCurrentFrame().GetTextureRegion());
	}
}

void AnimatedSprite::Update()
{
	if (currentAnimation->IsPlaying())
	{
		currentAnimation->Update();
		SetTextureRegion(currentAnimation->GetCurrentFrame().GetTextureRegion());
	}
}