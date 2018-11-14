#pragma once

#include <map>
#include "AbstractReader.h"

using Dictionary = std::map<std::string, std::string>;

class DictionaryReader : public AbstractReader<Dictionary>
{
public:
	std::shared_ptr<Dictionary> Read(std::string filePath, ContentManager &contentManager) override;
};