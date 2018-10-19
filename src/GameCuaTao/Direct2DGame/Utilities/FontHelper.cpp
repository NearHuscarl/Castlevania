#include <ft2build.h>
#include FT_FREETYPE_H
#include "FontHelper.h"
#include "FileLogger.h"

std::string FontHelper::GetFamilyName(std::string filePath)
{
	auto library = FT_Library{}; // handle to library
	auto face = FT_Face{};       // handle to face object

	auto error = FT_Init_FreeType(&library);
	if (error)
	{
		FileLogger::GetInstance().Error("FT_Init_FreeType() failed with error code: " + error);
		return "";
	}

	error = FT_New_Face(library, filePath.c_str(), 0, &face);
	if (error)
	{
		FileLogger::GetInstance().Error("FT_New_Face() failed with error code: " + error);
		return "";
	}

	return face->family_name;
}
