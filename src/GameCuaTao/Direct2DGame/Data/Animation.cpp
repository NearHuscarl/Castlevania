#include "Animation.h"
#include "../Utilities/Stopwatch.h"

Animation::Animation()
{
}

Animation::Animation(std::shared_ptr<Texture> texture, unsigned long defaultTime)
{
	this->texture = texture;
	this->defaultTime = defaultTime;

	this->lastFrameTime = 0;
	this->currentFrame = -1;
}

AnimationFrame Animation::GetCurrentFrame()
{
	if (currentFrame == -1)
		return frames[0];

	return frames[currentFrame];
}

void Animation::Add(Sprite sprite, unsigned long time)
{
	if (time == 0)
		time = this->defaultTime;

	auto frame = AnimationFrame{ sprite, time };
	frames.push_back(frame);
}

void Animation::Update()
{
	auto now = Stopwatch::GetTimeStamp();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		auto frameTimeout = frames[currentFrame].GetTime();
		if (now - lastFrameTime > frameTimeout)
		{
			currentFrame++;
			lastFrameTime = now;

			if (currentFrame == frames.size())
				currentFrame = 0;
		}
	}
}

void Animation::Draw(SpriteBatch &spriteBatch, Vector2 position, Color color, SpriteEffects effects)
{
	frames[currentFrame].GetSprite().Draw(spriteBatch, *texture, position, color, effects);
}