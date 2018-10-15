#include "ContentReader.h"
#include "ContentManager.h"

ContentReader::ContentReader()
{
}

ContentReader::ContentReader(ContentManager *contentManager)
{
	this->contentManager = contentManager;
}

template<>
std::shared_ptr<Texture> ContentReader::ReadAsset<Texture>(std::string filePath)
{
	return textureReader.Read(filePath, *contentManager);
}

template<>
std::shared_ptr<AnimationDict> ContentReader::ReadAsset<AnimationDict>(std::string filePath)
{
	return animationReader.Read(filePath, *contentManager);
}