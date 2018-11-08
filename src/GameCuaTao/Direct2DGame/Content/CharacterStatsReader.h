#pragma once

#include "AbstractReader.h"
#include "../Data/CharacterStats.h"

class CharacterStatsReader : public AbstractReader<CharacterStats>
{
public:
	std::shared_ptr<CharacterStats> Read(std::string filePath, ContentManager &contentManager) override;
};