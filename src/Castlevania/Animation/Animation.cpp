#include "Animation.h"

Animation::Animation(unsigned long defaultTime)
{
	this->defaultTime = defaultTime;
	this->lastFrameTime = -1;
	this->currentFrame = -1;
}

void Animation::Add(Sprite *sprite, unsigned long time)
{
	if (time == 0)
		time = this->defaultTime;

	AnimationFrame *frame = new AnimationFrame(sprite, time);
	frames.push_back(frame);
}

void Animation::Update()
{
	unsigned long now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		unsigned long frameTimeout = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > frameTimeout)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
		}

	}
}

void Animation::Draw(ID3DXSprite *spriteHandler, float x, float y)
{
	frames[currentFrame]->GetSprite()->Draw(spriteHandler, x, y);
}