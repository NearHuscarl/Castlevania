#pragma once

#include "AbstractReader.h"
#include "../Graphics/SpriteFont.h"

class SpriteFontReader : public AbstractReader<SpriteFont>
{
public:
	std::shared_ptr<SpriteFont> Read(std::string filePath, ContentManager &contentManager) override;
};