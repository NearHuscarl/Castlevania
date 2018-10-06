#include <filesystem>
#include "DxTextureManager.h"
#include "../Utilities/WindowUtil.h"
#include "../Utilities/Debug.h"

GDevicePtr DxTextureManager::device;
std::string DxTextureManager::rootDirectory;


void DxTextureManager::Initialize(GDevicePtr device, std::string rootDirectory)
{
	DxTextureManager::device = device;
	DxTextureManager::rootDirectory = rootDirectory;
}

// Override me
void DxTextureManager::LoadResource()
{
}

GTexturePtr DxTextureManager::Get(std::string entity)
{
	return textures[entity];
}

GTexturePtr DxTextureManager::GetResourceFromFile(std::string filePathStr, D3DCOLOR transparentColor)
{
	D3DXIMAGE_INFO info;
	std::wstring filePath = WindowUtil::String2WString(DxTextureManager::rootDirectory + "\\" + filePathStr);
	HRESULT result = D3DXGetImageInfoFromFile(filePath.c_str(), &info);
	if (result != D3D_OK)
	{
		DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n", filePath);
		return nullptr;
	}

	GTexturePtr texture;

	result = D3DXCreateTextureFromFileEx(
		device,								// Pointer to Direct3D device object
		filePath.c_str(),							// Path to the image to load
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
		nullptr,
		&texture);								// Created texture pointer

	if (result != D3D_OK)
	{
		OutputDebugString(L"[ERROR] CreateTextureFromFile failed\n");
		return nullptr;
	}

	DebugOut(L"[INFO] Texture loaded Ok: %s \n", filePath);

	return texture;
}