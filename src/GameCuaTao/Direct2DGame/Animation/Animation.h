#pragma once

#include <vector>
#include "AnimationFrame.h"

class Animation
{
public:
	Animation();
	Animation(std::shared_ptr<Texture> texture, unsigned long defaultTime = 100);

	void Add(Sprite sprite, unsigned long time = 0);
	void Update();
	void Draw(SpriteBatch &spriteBatch, Vector2 position, Color color, SpriteEffects effects);

private:
	unsigned long lastFrameTime;
	unsigned long defaultTime;
	int currentFrame;

	std::vector<AnimationFrame> frames;
	std::shared_ptr<Texture> texture;
};
