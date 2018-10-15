#include "AnimationFrame.h"

AnimationFrame::AnimationFrame()
{
}

AnimationFrame::AnimationFrame(Sprite sprite, unsigned long time)
{
	this->sprite = sprite;
	this->time = time;
}

unsigned long AnimationFrame::GetTime()
{
	return time;
}

Sprite &AnimationFrame::GetSprite()
{
	return sprite;
}