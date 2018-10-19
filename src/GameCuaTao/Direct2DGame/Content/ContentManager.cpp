#include "ContentManager.h"
#include "Library/directx/DSUtil.h"

ContentManager::ContentManager(std::shared_ptr<ServiceProvider> serviceProvider)
{
	this->serviceProvider = serviceProvider;
	this->contentReader = ContentReader{ std::shared_ptr<ContentManager>(this) };
}

void ContentManager::SetRootDirectory(std::string path)
{
	rootDirectory = Path{ path }.make_preferred().string();
}

ServiceProvider &ContentManager::GetServiceProvider()
{
	return *serviceProvider;
}

template<typename T>
std::shared_ptr<T> ContentManager::Load(std::string assetName)
{
	assetName = Path{ assetName }.make_preferred().string(); // Replace path seperator '/' with '\\'

	auto it = loadedAssets.find(assetName);
	if (it != loadedAssets.end()) // Asset already loaded before, just return it
	{
		return std::any_cast<std::shared_ptr<T>>(loadedAssets[assetName]);
	}
	
	loadedAssets.emplace(assetName, ReadAsset<T>(assetName));

	return std::any_cast<std::shared_ptr<T>>(loadedAssets[assetName]);
}

template<typename T>
std::shared_ptr<T> ContentManager::ReadAsset(std::string assetName)
{
	auto path = (rootDirectory / assetName).string();

	return contentReader.ReadAsset<T>(path);
}

template std::shared_ptr<AnimationDict> ContentManager::Load<AnimationDict>(std::string assetName);
template std::shared_ptr<AnimationDict> ContentManager::ReadAsset<AnimationDict>(std::string assetName);

template std::shared_ptr<Texture> ContentManager::Load<Texture>(std::string assetName);
template std::shared_ptr<Texture> ContentManager::ReadAsset<Texture>(std::string assetName);

template std::shared_ptr<Sound> ContentManager::Load<Sound>(std::string assetName);
template std::shared_ptr<Sound> ContentManager::ReadAsset<Sound>(std::string assetName);