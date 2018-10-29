#pragma once

#include <map>
#include "AbstractReader.h"
#include "../Graphics/SpriteFont.h"
#include "../Graphics/FontDescription.h"

class SpriteFontReader : public AbstractReader<SpriteFont>
{
public:
	std::shared_ptr<SpriteFont> Read(std::string filePath, ContentManager &contentManager) override;

private:
	FontDescription ReadFontConfig(std::string configFile);
};