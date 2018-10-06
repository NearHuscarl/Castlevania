#include "TextureManager.h"
#include "../Base/Entity.h"

TextureManager *TextureManager::instance = nullptr;


TextureManager *TextureManager::GetInstance()
{
	if (instance == nullptr)
		instance = new TextureManager();
	return instance;
}

void TextureManager::LoadResource()
{
	// TODO: remove background color by making all spritesheets using the same bg color
	textures[MARIO] = GetResourceFromFile("mario.png", D3DCOLOR_XRGB(176, 224, 248));
}