#include "Animation.h"
#include "SpriteManager.h"


Animation::Animation(int defaultTime)
{
	this->defaultTime = defaultTime;
	this->lastFrameTime = -1;
	this->currentFrame = -1;
}

void Animation::Add(int spriteId, DWORD time)
{
	int t = time;
	if (time == 0) t = this->defaultTime;

	Sprite *sprite = SpriteManager::GetInstance()->Get(spriteId);
	AnimationFrame *frame = new AnimationFrame(sprite, t);
	frames.push_back(frame);
}

void Animation::Render(float x, float y)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD frameTimeout = frames[currentFrame]->GetTime();
		if (now - lastFrameTime > frameTimeout)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
			//DebugOut(L"now: %d, lastFrameTime: %d, t: %d\n", now, lastFrameTime, t);
		}

	}

	frames[currentFrame]->GetSprite()->Draw(x, y);
}