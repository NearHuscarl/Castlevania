#include "TextureReader.h"
#include "../GraphicsDevice.h"
#include "../Utilities/FileLogger.h"
#include "../Utilities/WinHelper.h"
#include "ContentManager.h"
#include "LoadContentException.h"

std::shared_ptr<Texture> TextureReader::Read(std::string filePathStr, ContentManager &contentManager)
{
	auto info = ImageInfo{};
	auto filePath = WinHelper::s2ws(filePathStr);

	auto result = D3DXGetImageInfoFromFile(filePath.c_str(), &info);
	if (result != D3D_OK)
	{
		throw LoadContentException("GetImageInfoFromFile failed: " + filePathStr);
	}

	auto graphicsDevice = contentManager.GetServiceProvider().Get<GraphicsDevice>();

	auto texture = ITexture_{ nullptr };
	auto renderDevice = graphicsDevice->GetRenderDevice();
	auto transparentColor = graphicsDevice->GetTransparentColor();

	result = D3DXCreateTextureFromFileEx(
		renderDevice,		                  // Pointer to Direct3D device object
		filePath.c_str(),					// Path to the image to load
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
		&texture);							// Created texture pointer

	if (result != D3D_OK)
	{
		throw LoadContentException("CreateTextureFromFile failed: " + filePathStr);
	}

	FileLogger::GetInstance().Info("Texture loaded Ok: " + filePathStr);

	return std::make_shared<Texture>(texture);
}