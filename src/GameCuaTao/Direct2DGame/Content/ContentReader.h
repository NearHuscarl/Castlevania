#pragma once

#include <string>
#include "TextureReader.h"
#include "AnimationReader.h"

class ContentManager;

class ContentReader
{
public:
	ContentReader();
	ContentReader(ContentManager *contentManager);

	template<typename T>
	std::shared_ptr<T> ReadAsset(std::string path);

private:
	ContentManager *contentManager;

	TextureReader textureReader;
	AnimationReader animationReader;
};