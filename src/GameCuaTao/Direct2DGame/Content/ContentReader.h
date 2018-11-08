#pragma once

#include <string>
#include "AnimationFactoryReader.h"
#include "CharacterStatsReader.h"
#include "SoundReader.h"
#include "SpriteFontReader.h"
#include "TextureReader.h"
#include "TiledMapReader.h"

class ContentManager;

class ContentReader
{
public:
	ContentReader(ContentManager &contentManager);

	template<typename T>
	std::shared_ptr<T> ReadAsset(std::string path);

private:
	ContentManager &contentManager;

	AnimationFactoryReader animationFactoryReader;
	CharacterStatsReader characterStatsReader;
	SoundReader soundReader;
	SpriteFontReader spriteFontReader;
	TextureReader textureReader;
	TiledMapReader tiledMapReader;
};