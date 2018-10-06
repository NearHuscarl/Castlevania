#pragma once

#include <string>
#include "Base/Graphics.h"
#include "Utilities/DirectX.h"

class Content
{
public:
	Content() {};
	Content(Graphics *graphics);

	GTexturePtr LoadTexture(std::string path);
	void SetRootDirectory(std::string path);

private:
	std::string rootDirectory;
	Graphics *graphics = nullptr;
};