#include "ContentReader.h"
#include "ContentManager.h"

ContentReader::ContentReader(ContentManager &contentManager) : contentManager{ contentManager }
{
}

template<>
std::shared_ptr<AnimationFactory> ContentReader::ReadAsset<AnimationFactory>(std::string filePath)
{
	return animationFactoryReader.Read(filePath, contentManager);
}

template<>
std::shared_ptr<CharacterStats> ContentReader::ReadAsset<CharacterStats>(std::string filePath)
{
	return characterStatsReader.Read(filePath, contentManager);
}

template<>
std::shared_ptr<Sound> ContentReader::ReadAsset<Sound>(std::string filePath)
{
	return soundReader.Read(filePath, contentManager);
}

template<>
std::shared_ptr<SpriteFont> ContentReader::ReadAsset<SpriteFont>(std::string filePath)
{
	return spriteFontReader.Read(filePath, contentManager);
}

template<>
std::shared_ptr<Texture> ContentReader::ReadAsset<Texture>(std::string filePath)
{
	return textureReader.Read(filePath, contentManager);
}

template<>
std::shared_ptr<TiledMap> ContentReader::ReadAsset<TiledMap>(std::string filePath)
{
	return tiledMapReader.Read(filePath, contentManager);
}