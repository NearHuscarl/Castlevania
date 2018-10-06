#pragma once

#include <map>
#include "../Base/Graphics.h"

typedef std::map<std::string, GTexturePtr> TextureDict;

// Manage texture database
class DxTextureManager
{
public:
	static void Initialize(GDevicePtr device, std::string rootDirectory = "Content");
	virtual void LoadResource();
	GTexturePtr Get(std::string entity);
	
protected:
	GTexturePtr GetResourceFromFile(std::string filePath, D3DCOLOR transparentColor);
	TextureDict textures;

private:
	static GDevicePtr device;
	static std::string rootDirectory; // TODO: remove static
};