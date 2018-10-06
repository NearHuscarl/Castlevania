#pragma once

#include "DxTextureManager.h"

class TextureManager : public DxTextureManager
{
public:
	static TextureManager *GetInstance();

	void LoadResource() override;

private:
	static TextureManager *instance;
};