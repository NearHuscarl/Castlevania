#include "AnimationManager.h"
#include "AnimationSettings.h"
#include "SpriteManager.h"
#include "../Base/Entity.h"
#include "../Models/Mario.h"

AnimationManager *AnimationManager::instance = nullptr;

AnimationManager *AnimationManager::GetInstance()
{
	if (instance == nullptr)
		instance = new AnimationManager();
	return instance;
}

void AnimationManager::LoadResource(ContentManager *content)
{
	IDirect3DTexture9 *marioTexture = content->Load<IDirect3DTexture9*>("mario.png");

	AddSprite(MARIO_WALK_RIGHT_01, BoundingBox(246, 154, 260, 181), marioTexture);
	AddSprite(MARIO_WALK_RIGHT_02, BoundingBox(275, 154, 290, 181), marioTexture);
	AddSprite(MARIO_WALK_RIGHT_03, BoundingBox(304, 154, 321, 181), marioTexture);

	AddSprite(MARIO_WALK_LEFT_01, BoundingBox(186, 154, 200, 181), marioTexture);
	AddSprite(MARIO_WALK_LEFT_02, BoundingBox(155, 154, 170, 181), marioTexture);
	AddSprite(MARIO_WALK_LEFT_03, BoundingBox(125, 154, 140, 181), marioTexture);

	AddAnimation(MARIO_IDLE_RIGHT, 100, { MARIO_WALK_RIGHT_01 });
	AddAnimation(MARIO_WALK_RIGHT, 100, { MARIO_WALK_RIGHT_01, MARIO_WALK_RIGHT_02, MARIO_WALK_RIGHT_03 });
	AddAnimation(MARIO_IDLE_LEFT,  100, { MARIO_WALK_LEFT_01 });
	AddAnimation(MARIO_WALK_LEFT,  100, { MARIO_WALK_LEFT_01, MARIO_WALK_LEFT_02, MARIO_WALK_LEFT_03 });
}

void AnimationManager::AddSprite(std::string spriteID, BoundingBox boundingBox, IDirect3DTexture9 *texture)
{
	SpriteManager::GetInstance()->Add(spriteID, boundingBox, texture);
}

void AnimationManager::AddAnimation(std::string animationID, int animateTime, std::vector<std::string> spriteIDs)
{
	Animation *animation = new Animation(animateTime);
	Sprite *sprite = nullptr;

	for (auto spriteID : spriteIDs)
	{
		sprite = SpriteManager::GetInstance()->Get(spriteID);
		animation->Add(sprite);
	}

	animations[animationID] = animation;
}

Animation * AnimationManager::GetAnimation(std::string animationID)
{
	return animations[animationID];
}
