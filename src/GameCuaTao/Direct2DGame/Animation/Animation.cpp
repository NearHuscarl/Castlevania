#include "Animation.h"
#include "../Utilities/TimeHelper.h"

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

void Animation::Add(Sprite sprite, unsigned long time)
{
	if (time == 0)
		time = this->defaultTime;

	auto frame = AnimationFrame{ sprite, time };
	frames.push_back(frame);
}

void Animation::Update()
{
	auto now = TimeHelper::GetTickNow();
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

void Animation::Draw(ISpriteBatch_ spriteBatch, Vector position, SpriteEffects effects)
{
	frames[currentFrame].GetSprite().Draw(spriteBatch, *texture, position, effects);
}