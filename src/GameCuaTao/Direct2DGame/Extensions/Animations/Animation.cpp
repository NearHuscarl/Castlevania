#include "Animation.h"
#include "../../MathHelper.h"
#include "../../Utilities/Stopwatch.h"

Animation::Animation(std::string name, int defaultTime, bool isLooping)
{
	this->name = name;
	this->defaultTime = defaultTime;
	this->isLooping = isLooping;

	Reset();
}

std::string Animation::GetName()
{
	return name;
}

AnimationFrame Animation::GetCurrentFrame()
{
	return frames[GetCurrentFrameIndex()];
}

int Animation::GetCurrentFrameIndex()
{
	auto frameNow = currentFrame;

	// Not the most elegant way to get current frame but it works for now
	frameNow = MathHelper::Max(frameNow, 0);
	frameNow = MathHelper::Min(frameNow, (int)frames.size() - 1);

	return frameNow;
}

void Animation::SetElapsedTime(float elapsed)
{
	auto frameTime = frames[GetCurrentFrameIndex()].GetTime();
	auto elaspedTime =  frameTime * elapsed;
	auto now = Stopwatch::GetTimeStamp();
	
	lastFrameTime = now - (int)elaspedTime;
}

void Animation::Stop()
{
	auto now = Stopwatch::GetTimeStamp();
	
	elaspedFrameTime = now - lastFrameTime;
	isPaused = true;
}

void Animation::Continue()
{
	if (!isPaused)
		return;

	auto now = Stopwatch::GetTimeStamp();

	lastFrameTime = now - elaspedFrameTime;
	isPaused = false;
}

bool Animation::IsPlaying()
{
	return !isPaused && !isComplete;
}

bool Animation::IsComplete()
{
	return isComplete;
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
	if (isComplete)
		return;

	auto now = Stopwatch::GetTimeStamp();

	if (currentFrame == -1)
	{
		currentFrame = 0;
		if (lastFrameTime == 0) // Set to time now unless is set by SetElapsedTime() before that
			lastFrameTime = now;
		return;
	}

	auto frameTime = frames[currentFrame].GetTime();
	
	if (now - lastFrameTime > frameTime)
	{
		currentFrame++;
		lastFrameTime = now;

		if (currentFrame == frames.size())
		{
			if (!isLooping)
				isComplete = true;
			else
				currentFrame = 0;
		}
	}
}

void Animation::Reset()
{
	isComplete = false;

	lastFrameTime = 0;
	currentFrame = -1;
}
