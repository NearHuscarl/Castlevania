#pragma once

#include <unordered_map>
#include "../Views/Graphics.h"


/*
	Manage texture database
*/
class TextureManager
{
public: 
	static TextureManager *GetInstance();

	void Initialize(Graphics *graphics);

	void Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor);
	GTexturePtr Get(unsigned int i);
	
	void Draw(float x, float y, GTexturePtr texture);
	void Draw(float x, float y, GTexturePtr texture, int left, int top, int right, int bottom);

private:
	static TextureManager *instance;

	Graphics *graphics;
	std::unordered_map<int, GTexturePtr> textures;
};