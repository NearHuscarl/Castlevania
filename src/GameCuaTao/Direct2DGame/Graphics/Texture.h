#pragma once

#include "../Device.h"

class Texture
{
public:
	Texture(ITexture_ texture, ImageInfo info);
	ITexture_ Get();
	
	int Width();
	int Height();

	ImageInfo &GetInfo();

private:
	ITexture_ texture;
	ImageInfo info;
};