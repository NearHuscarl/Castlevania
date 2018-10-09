#pragma once

#include <string>
#include "GraphicsDevice.h"

class ContentReader
{
public:
	ContentReader();

	template<typename T>
	T ReadAsset(std::wstring path, GraphicsDevice &graphicsDevice);
};