//#include <Windows.h>

#include "../Utilities/Debug.h"
#include "../EntryPoint.h"
#include "TextureManager.h"

TextureManager *TextureManager::instance = NULL;


TextureManager *TextureManager::GetInstance()
{
	if (instance == NULL)
	{
		instance = new TextureManager();
	}
	return instance;
}

void TextureManager::Initialize(Graphics *graphics)
{
	this->graphics = graphics;
}

void TextureManager::Add(int id, LPCWSTR filePath, D3DCOLOR transparentColor)
{
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(filePath, &info);
	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n", filePath);
		return;
	}

	GDevicePtr d3ddv = graphics->GetDirect3DDevice();
	GTexturePtr texture;

	result = D3DXCreateTextureFromFileEx(
		d3ddv,								// Pointer to Direct3D device object
		filePath,							// Path to the image to load
		info.Width,							// Texture width
		info.Height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transparentColor,			
		&info,
		NULL,
		&texture);								// Created texture pointer

	if (result != D3D_OK)
	{
		OutputDebugString(L"[ERROR] CreateTextureFromFile failed\n");
		return;
	}

	textures[id] = texture;

	DebugOut(L"[INFO] Texture loaded Ok: id=%d, %s \n", id, filePath);
}

GTexturePtr TextureManager::Get(unsigned int i)
{
	return textures[i];
}

/*
	Utility function to wrap Direct3DSpritePtr::Draw
*/
void TextureManager::Draw(float x, float y, GTexturePtr texture)
{
	D3DXVECTOR3 p(x, y, 0);
	graphics->GetSpriteHandler()->Draw(texture, NULL, NULL, &p, D3DCOLOR_XRGB(255, 255, 255));
}

void TextureManager::Draw(float x, float y, GTexturePtr texture, int left, int top, int right, int bottom)
{
	D3DXVECTOR3 p(x, y, 0);
	RECT r;
	r.left = left;
	r.top = top;
	r.right = right;
	r.bottom = bottom;

	GSpritePtr spriteHandler = graphics->GetSpriteHandler();
	spriteHandler->Draw(texture, &r, NULL, &p, D3DCOLOR_XRGB(255, 255, 255));
}