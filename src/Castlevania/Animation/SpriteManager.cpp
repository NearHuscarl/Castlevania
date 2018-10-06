#include "SpriteManager.h"
#include "TextureManager.h"
#include "AnimationSettings.h"
#include "../Base/Entity.h"

SpriteManager *SpriteManager::instance = nullptr;

SpriteManager *SpriteManager::GetInstance()
{
	if (instance == nullptr)
		instance = new SpriteManager();
	return instance;
}

void SpriteManager::LoadResource()
{
	GTexturePtr marioTexture = TextureManager::GetInstance()->Get(MARIO);

	Add(MARIO_WALK_RIGHT_01, BoundingBox(246, 154, 260, 181), marioTexture);
	Add(MARIO_WALK_RIGHT_02, BoundingBox(275, 154, 290, 181), marioTexture);
	Add(MARIO_WALK_RIGHT_03, BoundingBox(304, 154, 321, 181), marioTexture);

	Add(MARIO_WALK_LEFT_01, BoundingBox(186, 154, 200, 181), marioTexture);
	Add(MARIO_WALK_LEFT_02, BoundingBox(155, 154, 170, 181), marioTexture);
	Add(MARIO_WALK_LEFT_03, BoundingBox(125, 154, 140, 181), marioTexture);
}

void SpriteManager::Add(std::string id, BoundingBox boundingBox, GTexturePtr texture)
{
	Sprite *sprite = new Sprite(id, boundingBox, texture);
	sprites[id] = sprite;
}

Sprite *SpriteManager::Get(std::string id)
{
	return sprites[id];
}