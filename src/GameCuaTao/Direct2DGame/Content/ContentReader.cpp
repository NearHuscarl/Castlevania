#include "ContentReader.h"
#include "ContentManager.h"

ContentReader::ContentReader()
{
}

ContentReader::ContentReader(std::shared_ptr<ContentManager> contentManager)
{
	this->contentManager = contentManager;
}

template<>
std::shared_ptr<AnimationDict> ContentReader::ReadAsset<AnimationDict>(std::string filePath)
{
	return animationReader.Read(filePath, *contentManager);
}

template<>
std::shared_ptr<Sound> ContentReader::ReadAsset<Sound>(std::string filePath)
{
	return soundReader.Read(filePath, *contentManager);
}

template<>
std::shared_ptr<SpriteFont> ContentReader::ReadAsset<SpriteFont>(std::string filePath)
{
	return spriteFontReader.Read(filePath, *contentManager);
}

template<>
std::shared_ptr<Texture> ContentReader::ReadAsset<Texture>(std::string filePath)
{
	return textureReader.Read(filePath, *contentManager);
}