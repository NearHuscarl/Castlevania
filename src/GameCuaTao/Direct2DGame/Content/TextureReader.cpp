#include "TextureReader.h"
#include "ContentManager.h"
#include "LoadContentException.h"
#include "../Graphics/GraphicsDevice.h"
#include "../Utilities/FileLogger.h"
#include "../Utilities/WinHelper.h"

std::shared_ptr<Texture> TextureReader::Read(std::string filePathStr, ContentManager &contentManager)
{
	auto info = ImageInfo{};
	auto filePath = WinHelper::s2ws(filePathStr);
	auto result = D3DXGetImageInfoFromFile(filePath.c_str(), &info);

	if (result != D3D_OK)
	{
		throw LoadContentException("D3DXGetImageInfoFromFile() failed: " + filePathStr);
	}

	auto texture = ITexture_{ nullptr };
	auto graphicsDevice = contentManager.GetServiceProvider().Get<GraphicsDevice>();
	auto renderDevice = graphicsDevice->GetRenderDevice();
	auto transparentColor = graphicsDevice->GetTransparentColor();

	result = D3DXCreateTextureFromFileEx(
		renderDevice,		            // Direct3D device object
		filePath.c_str(),					// Path to the image to load
		info.Width,							// Texture width
		info.Height,						// Texture height
		1,                            // mip-map levels (1 for no chain)
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,               // surface format (default)
		D3DPOOL_DEFAULT,              // memory class for the texture
		D3DX_DEFAULT,                 // image filter
		D3DX_DEFAULT,                 // mip filter
		transparentColor.Get(),       // color key for transparency
		&info,                        // image file info
		nullptr,                      // color palette
		&texture);							// Created texture pointer

	if (result != D3D_OK)
	{
		throw LoadContentException("D3DXCreateTextureFromFileEx() failed: " + filePathStr);
	}

	FileLogger::GetInstance().Info("Texture loaded Ok: " + filePathStr);

	return std::make_shared<Texture>(texture, info);
}