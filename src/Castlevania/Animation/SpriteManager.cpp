#include "SpriteManager.h"
#include "AnimationSettings.h"
#include "../Base/Entity.h"

SpriteManager *SpriteManager::instance = nullptr;

SpriteManager *SpriteManager::GetInstance()
{
	if (instance == nullptr)
		instance = new SpriteManager();
	return instance;
}

void SpriteManager::Add(std::string spriteID, BoundingBox boundingBox, IDirect3DTexture9 *texture)
{
	Sprite *sprite = new Sprite(spriteID, boundingBox, texture);
	sprites[spriteID] = sprite;
}

Sprite *SpriteManager::Get(std::string id)
{
	return sprites[id];
}