#include "AnimationManager.h"

AnimationManager * AnimationManager::instance = NULL;


AnimationManager * AnimationManager::GetInstance()
{
	if (instance == NULL)
		instance = new AnimationManager();
	return instance;
}

void AnimationManager::Add(int id, Animation *ani)
{
	animations[id] = ani;
}

Animation *AnimationManager::Get(int id)
{
	return animations[id];
}