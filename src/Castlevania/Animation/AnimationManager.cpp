#include "AnimationManager.h"
#include "AnimationSettings.h"
#include "../Base/Entity.h"
#include "../Models/Mario.h"

AnimationManager *AnimationManager::instance = nullptr;

AnimationManager *AnimationManager::GetInstance()
{
	if (instance == nullptr)
		instance = new AnimationManager();
	return instance;
}

void AnimationManager::LoadResource()
{
	AddAnimation(MARIO_IDLE_RIGHT, 100, { MARIO_WALK_RIGHT_01 });
	AddAnimation(MARIO_WALK_RIGHT, 100, { MARIO_WALK_RIGHT_01, MARIO_WALK_RIGHT_02, MARIO_WALK_RIGHT_03 });
	AddAnimation(MARIO_IDLE_LEFT,  100, { MARIO_WALK_LEFT_01 });
	AddAnimation(MARIO_WALK_LEFT,  100, { MARIO_WALK_LEFT_01, MARIO_WALK_LEFT_02, MARIO_WALK_LEFT_03 });
}

void AnimationManager::AddAnimation(std::string animationID, int animateTime, std::vector<std::string> sprites)
{
	Animation *animation = new Animation(animateTime);
	for (auto sprite : sprites)
	{
		animation->Add(sprite);
	}

	animations[animationID] = animation;
}

Animation * AnimationManager::GetAnimation(std::string animationID)
{
	return animations[animationID];
}
