#pragma once

#include "../Device.h"

class Texture
{
public:
	Texture(ITexture_);
	ITexture_ Get();

private:
	ITexture_ texture;
};