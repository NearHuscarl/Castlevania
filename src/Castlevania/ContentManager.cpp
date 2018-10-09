#include "ContentManager.h"
#include "Game.h"
#include "Utilities/WindowUtil.h"
#include "Utilities/Debug.h"

ContentManager::ContentManager()
{
}

ContentManager::ContentManager(Game *game)
{
	this->game = game;
}

void ContentManager::SetRootDirectory(std::string path)
{
	rootDirectory = path;
}

template<typename T>
T ContentManager::Load(std::string assetName)
{
	// TODO: handle path seperator
	// var key = assetName.Replace('/', '\\');

	auto it = loadedAssets.find(assetName);
	if (it != loadedAssets.end()) // Asset already loaded before, just return it
	{
		return std::any_cast<T>(loadedAssets[assetName]);
	}

	T asset = ReadAsset<T>(assetName);

	loadedAssets[assetName] = asset;
	return asset;
}

template<typename T>
T ContentManager::ReadAsset(std::string assetName)
{
	std::string pathStr = rootDirectory + "\\" + assetName;
	std::wstring path = WindowUtil::String2WString(pathStr);

	return contentReader.ReadAsset<T>(path, game->GetGraphicsDevice());
}

//template std::map<std::string, IDirect3DTexture9*> ContentManager::loadedAssets<IDirect3DTexture9*>;
template IDirect3DTexture9* ContentManager::Load<IDirect3DTexture9*>(std::string assetName);
template IDirect3DTexture9* ContentManager::ReadAsset<IDirect3DTexture9*>(std::string assetName);