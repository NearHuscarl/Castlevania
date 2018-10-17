#pragma once

#include <string>
#include "TextureReader.h"
#include "AnimationReader.h"

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

	TextureReader textureReader;
	AnimationReader animationReader;
};