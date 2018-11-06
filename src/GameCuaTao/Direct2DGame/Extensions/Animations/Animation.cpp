#include "Animation.h"
#include "../../Utilities/Stopwatch.h"

Animation::Animation(std::string name, int defaultTime, bool isLooping)
{
	this->name = name;
	this->defaultTime = defaultTime;
	this->isLooping = isLooping;

	this->lastFrameTime = 0;
	this->currentFrame = -1;
}

std::string Animation::GetName()
{
	return name;
}

AnimationFrame Animation::GetCurrentFrame()
{
	if (currentFrame == -1)
		return frames[0];

	return frames[currentFrame];
}

bool Animation::IsComplete()
{
	if (!isLooping && currentFrame == frames.size())
		return true;

	return false;
}

void Animation::Add(TextureRegion textureRegion, int time)
{
	if (time == 0)
		time = this->defaultTime;

	auto frame = AnimationFrame{ textureRegion, time };
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