#pragma once

#include <string>
#include <map>
#include <any>
#include "ContentReader.h"

class Game;

class ContentManager
{
public:
	ContentManager();
	ContentManager(Game *game);

	void SetRootDirectory(std::string path);

	template<typename T>
	T Load(std::string assetName);

private:
	std::string rootDirectory;
	std::map<std::string, std::any> loadedAssets;

	Game *game;

	//template<typename T>
	//static std::map<std::string, T> loadedAssets;

	ContentReader contentReader;

	template<typename T>
	T ReadAsset(std::string assetName);
};