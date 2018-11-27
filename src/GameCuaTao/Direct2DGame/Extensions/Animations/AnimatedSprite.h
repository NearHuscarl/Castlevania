#pragma once

#include "../Sprites/Sprite.h"
#include "AnimationFactory.h"

class AnimatedSprite : public Sprite
{
public:
	AnimatedSprite(std::shared_ptr<AnimationFactory> animationFactory);
	AnimatedSprite(std::shared_ptr<AnimationFactory> animationFactory, std::vector<std::string> animations);

	Animation &GetCurrentAnimation();
	bool AnimateComplete();

	void Play(std::string name);
	void PlayCached(std::string name); // Play the animation without reset its last state

	void Update();

private:
	std::shared_ptr<AnimationFactory> animationFactory;
	AnimationDict animations;
	Animation *currentAnimation;
};