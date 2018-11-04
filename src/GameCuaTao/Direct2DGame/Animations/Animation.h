#pragma once

#include <vector>
#include "AnimationFrame.h"

class Animation
{
public:
	Animation();
	Animation(std::string name, std::shared_ptr<Texture> texture, int defaultTime = 100, bool isLooping = true);

	std::string GetName();
	AnimationFrame GetCurrentFrame();

	bool IsComplete();

	void Add(Sprite sprite, int time = 0);
	void Update();
	void Draw(SpriteBatch &spriteBatch, Vector2 position, Color color, SpriteEffects effects);

private:
	bool isLooping;

	int lastFrameTime;
	int defaultTime;
	int currentFrame;

	std::string name;
	std::vector<AnimationFrame> frames;
	std::shared_ptr<Texture> texture;
};
