#pragma once

#include <unordered_map>
#include "AbstractReader.h"
#include "../Extensions/TextureRegion.h"

using Spritesheet = std::unordered_map<std::string, TextureRegion>;

class SpritesheetReader : public AbstractReader<Spritesheet>
{
public:
	std::shared_ptr<Spritesheet> Read(std::string filePath, ContentManager &contentManager) override;
};