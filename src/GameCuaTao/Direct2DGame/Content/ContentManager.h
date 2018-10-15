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
	ContentManager(ServiceProvider &serviceProvider);
	void SetRootDirectory(std::string path);

	template<typename T>
	std::shared_ptr<T> Load(std::string assetName);

	ServiceProvider &GetServiceProvider();

private:
	Path rootDirectory;
	AssetDict loadedAssets;

	ServiceProvider &serviceProvider;
	ContentReader contentReader;

	template<typename T>
	std::shared_ptr<T> ReadAsset(std::string assetName);
};