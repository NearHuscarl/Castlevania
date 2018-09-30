#pragma once

#include <unordered_map>
#include "Sprite.h"


class SpriteManager
{
public:
	void Add(int id, int left, int top, int right, int bottom, GTexturePtr tex);
	Sprite *Get(int id);

	static SpriteManager *GetInstance();

private:
	static SpriteManager *instance;

	std::unordered_map<int, Sprite*> sprites;
};