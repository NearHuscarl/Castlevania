#include <d3dx9.h>
#include "ContentReader.h"
#include "Utilities/FileLogger.h"
#include "Utilities/WinHelper.h"


ContentReader::ContentReader()
{
}

template<>
IDirect3DTexture9* ContentReader::ReadAsset<IDirect3DTexture9*>(std::wstring filePath, GraphicsDevice &graphicsDevice)
{
	D3DXIMAGE_INFO info;

	HRESULT result = D3DXGetImageInfoFromFile(filePath.c_str(), &info);
	if (result != D3D_OK)
	{
		FileLogger::GetInstance()->Error("GetImageInfoFromFile failed: " + WinHelper::ws2s(filePath));
		return nullptr;
	}

	IDirect3DTexture9 *texture = nullptr;
	IDirect3DDevice9 *device = graphicsDevice.GetDevice();
	D3DCOLOR transColor = graphicsDevice.GetTransparentColor();

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
		FileLogger::GetInstance()->Error("CreateTextureFromFile failed");
		return nullptr;
	}

	FileLogger::GetInstance()->Info("Texture loaded Ok: " + WinHelper::ws2s(filePath));

	return texture;
}