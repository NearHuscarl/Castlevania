#pragma once

#include <map>
#include "Sprite.h"

typedef std::map<std::string, Sprite*> SpriteDict;

class SpriteManager
{
public:
	static SpriteManager *GetInstance();

	void LoadResource();
	void Add(std::string id, BoundingBox boundingBox, GTexturePtr texture);
	Sprite *Get(std::string id);

private:
	static SpriteManager *instance;

	SpriteDict sprites;
};