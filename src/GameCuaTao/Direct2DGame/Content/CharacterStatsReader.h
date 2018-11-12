#pragma once

#include <map>
#include "AbstractReader.h"

using CharacterStats = std::map<std::string, std::string>;

class CharacterStatsReader : public AbstractReader<CharacterStats>
{
public:
	std::shared_ptr<CharacterStats> Read(std::string filePath, ContentManager &contentManager) override;
};