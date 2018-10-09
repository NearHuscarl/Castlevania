#pragma once

#include <map>
#include "Sprite.h"
#include "../ContentManager.h"

using SpriteDict = std::map<std::string, Sprite*>;

class SpriteManager
{
public:
	static SpriteManager *GetInstance();

	void Add(std::string spriteID, BoundingBox boundingBox, IDirect3DTexture9 *texture);
	Sprite *Get(std::string id);

private:
	static SpriteManager *instance;

	SpriteDict sprites;
};