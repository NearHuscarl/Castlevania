#include <filesystem>
#include "Library/pugixml/pugixml.hpp"
#include "SpriteFontReader.h"
#include "ContentManager.h"
#include "LoadContentException.h"
#include "../GraphicsDeviceManager.h"
#include "../Utilities/FileLogger.h"
#include "../Utilities/FontHelper.h"
#include "../Utilities/WinHelper.h"

std::shared_ptr<SpriteFont> SpriteFontReader::Read(std::string configFile, ContentManager &contentManager)
{
	auto options = ReadFontConfig(configFile);

	if (options.directory == "")
		options.directory = Path{ configFile }.parent_path().string();
	else
		options.directory = (Path{ contentManager.GetRootDirectory() } / options.directory).string();

	auto filePathStr = (Path{ options.directory } / options.fontName).string();

	if (!std::filesystem::exists(filePathStr))
		throw LoadContentException("Font file not found: " + configFile);

	auto filePath = WinHelper::s2ws(filePathStr);
	auto graphics = contentManager.GetServiceProvider().Get<GraphicsDeviceManager>();

	AddFontResourceEx(filePath.c_str(), FR_PRIVATE, NULL);

	auto renderDevice = graphics->GetGraphicsDevice().GetRenderDevice();
	auto size = (int)options.size;
	auto bold = options.style == FontStyle::Bold ? FW_BOLD : FW_NORMAL;
	auto italic = options.style == FontStyle::Italic;
	auto familyName = WinHelper::s2ws(FontHelper::GetFamilyName(filePathStr));
	auto font = IFont_{ nullptr };

	auto result = D3DXCreateFont(
		renderDevice,         // Direct3D device object
		size,                 // Height
		0,                    // Width
		bold,                 // Weight
		1,                    // MipLevels
		italic,               // Italic
		DEFAULT_CHARSET,      // Charset
		OUT_DEFAULT_PRECIS,   // OutputPrecision
		ANTIALIASED_QUALITY,  // Quality
		FF_DONTCARE,          // PitchAndFamily
		familyName.c_str(),   // pFaceName
		&font);               // ppFont

	if (result != D3D_OK)
		throw LoadContentException("D3DXCreateFont() failed: " + filePathStr);
	
	return std::make_shared<SpriteFont>(font);
}

FontDescription SpriteFontReader::ReadFontConfig(std::string configFile)
{
	if (!Path{ configFile }.has_extension())
		configFile += ".spritefont";

	auto xmlDocument = pugi::xml_document{};
	auto result = xmlDocument.load_file(configFile.c_str());

	if (!result)
	{
		FileLogger::GetInstance().Error(result.description());
		throw LoadContentException(result.description());
	}

	auto fontNode = xmlDocument.child("GameContent").child("Font");
	auto options = FontDescription{};
	static auto fontStyles = std::map<std::string, FontStyle>
	{
		{ "Regular", FontStyle::Regular },
		{ "Bold", FontStyle::Bold },
		{ "Italic", FontStyle::Italic },
	};

	options.fontName = fontNode.child("FontName").text().as_string();
	options.directory = fontNode.child("Directory").text().as_string();
	options.size = fontNode.child("Size").text().as_float();
	options.style = fontStyles.at(fontNode.child("Style").text().as_string());

	return options;
}