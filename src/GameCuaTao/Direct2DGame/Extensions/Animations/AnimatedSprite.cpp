#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(std::shared_ptr<AnimationFactory> animationFactory) :
	Sprite{ animationFactory->Create()->GetCurrentFrame().GetTextureRegion() }
{
	this->currentAnimation = animationFactory->Create();
	this->animationFactory = animationFactory;
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