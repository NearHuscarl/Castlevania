#include "SpriteFontReader.h"
#include "ContentManager.h"
#include "LoadContentException.h"
#include "../GraphicsDevice.h"
#include "../Utilities/FontHelper.h"
#include "../Utilities/WinHelper.h"

std::shared_ptr<SpriteFont> SpriteFontReader::Read(std::string filePathStr, ContentManager &contentManager)
{
	auto filePath = WinHelper::s2ws(filePathStr);
	auto familyName = WinHelper::s2ws(FontHelper::GetFamilyName(filePathStr));
	auto font = IFont_{ nullptr };
	auto graphicsDevice = contentManager.GetServiceProvider().Get<GraphicsDevice>();
	auto renderDevice = graphicsDevice->GetRenderDevice();

	AddFontResourceEx(filePath.c_str(), FR_PRIVATE, NULL);
	auto result = D3DXCreateFont(
		renderDevice,         // Direct3D device object
		20,                   // Height
		0,                    // Width
		FW_NORMAL,            // Weight
		1,                    // MipLevels
		false,                // Italic
		DEFAULT_CHARSET,      // Charset
		OUT_DEFAULT_PRECIS,   // OutputPrecision
		ANTIALIASED_QUALITY,  // Quality
		FF_DONTCARE,          // PitchAndFamily
		familyName.c_str(),   // pFaceName
		&font);               // ppFont

	if (result != D3D_OK)
	{
		throw LoadContentException("D3DXCreateFont() failed: " + filePathStr);
	}

	return std::make_shared<SpriteFont>(font);
}
