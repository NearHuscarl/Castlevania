#pragma once

#include "../Sprites/Sprite.h"
#include "AnimationFactory.h"

class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite(std::shared_ptr<AnimationFactory> animationFactory);

	void Play(std::string name);
	void Update(float deltaTime);

private:
	std::shared_ptr<AnimationFactory> animationFactory;
	Animation *currentAnimation;
};