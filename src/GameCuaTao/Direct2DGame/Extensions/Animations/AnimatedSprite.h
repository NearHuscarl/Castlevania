#pragma once

#include "../Sprites/Sprite.h"
#include "AnimationFactory.h"

class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite(std::shared_ptr<AnimationFactory> animationFactory);

	bool AnimateComplete();

	void Play(std::string name);
	void Update();

private:
	std::shared_ptr<AnimationFactory> animationFactory;
	Animation *currentAnimation;
};