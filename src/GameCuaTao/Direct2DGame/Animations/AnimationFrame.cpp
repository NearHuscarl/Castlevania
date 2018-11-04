#include "AnimationFrame.h"

AnimationFrame::AnimationFrame()
{
}

AnimationFrame::AnimationFrame(Sprite sprite, int time)
{
	this->sprite = sprite;
	this->time = time;
}

int AnimationFrame::GetTime()
{
	return time;
}

Sprite &AnimationFrame::GetSprite()
{
	return sprite;
}