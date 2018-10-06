#include "Animation.h"
#include "SpriteManager.h"


Animation::Animation(int defaultTime)
{
	this->defaultTime = defaultTime;
	this->lastFrameTime = -1;
	this->currentFrame = -1;
}

void Animation::Add(std::string spriteId, DWORD time)
{
	if (time == 0)
		time = this->defaultTime;

	Sprite *sprite = SpriteManager::GetInstance()->Get(spriteId);
	AnimationFrame *frame = new AnimationFrame(sprite, time);
	frames.push_back(frame);
}

void Animation::Update()
{
	float now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		float frameTimeout = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > frameTimeout)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
		}

	}
}

void Animation::Render(float x, float y)
{
	frames[currentFrame]->GetSprite()->Draw(x, y);
}