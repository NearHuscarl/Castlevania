#include "Content.h"
#include "Utilities/WindowUtil.h"
#include "Utilities/Debug.h"

Content::Content(Graphics *graphics)
{
	this->graphics = graphics;
}

GTexturePtr Content::LoadTexture(std::string filePathStr)
{
	D3DXIMAGE_INFO info;
	std::wstring filePath = WindowUtil::String2WString(rootDirectory + "\\" + filePathStr);

	HRESULT result = D3DXGetImageInfoFromFile(filePath.c_str(), &info);
	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n", filePath);
		return nullptr;
	}

	GTexturePtr texture;
	GDevicePtr device = graphics->GetDirect3DDevice();
	D3DCOLOR transColor = graphics->GetTransparentColor();

	result = D3DXCreateTextureFromFileEx(
		device,		                        // Pointer to Direct3D device object
		filePath.c_str(),					// Path to the image to load
		info.Width,							// Texture width
		info.Height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transColor,
		&info,
		nullptr,
		&texture);							// Created texture pointer

	if (result != D3D_OK)
	{
		OutputDebugString(L"[ERROR] CreateTextureFromFile failed\n");
		return nullptr;
	}

	DebugOut(L"[INFO] Texture loaded Ok: %s \n", filePath);

	return texture;
}

void Content::SetRootDirectory(std::string path)
{
	rootDirectory = path;
}
