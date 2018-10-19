#pragma once

#include <string>
#include "AnimationReader.h"
#include "SoundReader.h"
#include "SpriteFontReader.h"
#include "TextureReader.h"

class ContentManager;

class ContentReader
{
public:
	ContentReader();
	ContentReader(std::shared_ptr<ContentManager> contentManager);

	template<typename T>
	std::shared_ptr<T> ReadAsset(std::string path);

private:
	std::shared_ptr<ContentManager> contentManager;

	AnimationReader animationReader;
	SoundReader soundReader;
	SpriteFontReader spriteFontReader;
	TextureReader textureReader;
};