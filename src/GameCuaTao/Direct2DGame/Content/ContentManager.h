#pragma once

#include <string>
#include <map>
#include <any>
#include <filesystem>
#include "../ServiceProvider.h"
#include "ContentReader.h"

using Path = std::filesystem::path;
using AssetDict = std::map<std::string, std::any>;

class ContentManager
{
public:
	ContentManager(std::shared_ptr<ServiceProvider> serviceProvider);

	std::string GetRootDirectory();
	void SetRootDirectory(std::string path);

	ServiceProvider &GetServiceProvider();

	template<typename T>
	std::shared_ptr<T> Load(std::string assetName);
	std::string ResolvePath(Path path, std::string filename); // Return asset relative path to rootDirectory

private:
	std::string rootDirectory;
	AssetDict loadedAssets;

	std::shared_ptr<ServiceProvider> serviceProvider;
	std::unique_ptr<ContentReader> contentReader;

	template<typename T>
	std::shared_ptr<T> ReadAsset(std::string assetName);
};

template<typename T>
inline std::shared_ptr<T> ContentManager::Load(std::string assetName)
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
inline std::shared_ptr<T> ContentManager::ReadAsset(std::string assetName)
{
	auto path = (Path{ rootDirectory } / assetName).string();

	return contentReader->ReadAsset<T>(path);
}