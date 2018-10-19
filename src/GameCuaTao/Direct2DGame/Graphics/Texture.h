#pragma once

#include "../Device.h"

class Texture
{
public:
	Texture(ITexture_ texture);
	ITexture_ Get();

private:
	ITexture_ texture;
};