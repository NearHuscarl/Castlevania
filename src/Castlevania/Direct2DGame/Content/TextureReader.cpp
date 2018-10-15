#include "TextureReader.h"
#include "../Utilities/FileLogger.h"
#include "../Utilities/WinHelper.h"
#include "ContentManager.h"
#include "LoadContentException.h"

std::shared_ptr<Texture> TextureReader::Read(std::string filePathStr, ContentManager &contentManager)
{
	D3DXIMAGE_INFO info;
	std::wstring filePath = WinHelper::s2ws(filePathStr);

	HRESULT result = D3DXGetImageInfoFromFile(filePath.c_str(), &info);
	if (result != D3D_OK)
	{
		throw LoadContentException("GetImageInfoFromFile failed: " + WinHelper::ws2s(filePath));
	}

	GraphicsDevice *graphicsDevice = contentManager.GetServiceProvider().Get<GraphicsDevice>();

	Texture texture = nullptr;
	DevicePtr device = graphicsDevice->GetDevice();
	D3DCOLOR transColor = graphicsDevice->GetTransparentColor();

	result = D3DXCreateTextureFromFileEx(
		device,		                  // Pointer to Direct3D device object
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
		throw LoadContentException("CreateTextureFromFile failed: " + WinHelper::ws2s(filePath));
	}

	FileLogger::GetInstance()->Info("Texture loaded Ok: " + WinHelper::ws2s(filePath));

	return std::make_shared<Texture>(texture);
}