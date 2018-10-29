#pragma once

#include <string>
#include "FontStyle.h"

struct FontDescription
{
	std::string fontName;
	std::string directory;
	float size;
	FontStyle style;
};