#include "SpriteManager.h"

SpriteManager *SpriteManager::instance = NULL;


SpriteManager *SpriteManager::GetInstance()
{
	if (instance == NULL)
		instance = new SpriteManager();
	return instance;
}

void SpriteManager::Add(int id, int left, int top, int right, int bottom, GTexturePtr texture)
{
	Sprite *s = new Sprite(id, left, top, right, bottom, texture);
	sprites[id] = s;
}

Sprite *SpriteManager::Get(int id)
{
	return sprites[id];
}