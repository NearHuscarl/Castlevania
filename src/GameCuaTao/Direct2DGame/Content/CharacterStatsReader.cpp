#include "Library/pugixml/pugixml.hpp"
#include "LoadContentException.h"
#include "../Utilities/FileLogger.h"
#include "CharacterStatsReader.h"

std::shared_ptr<CharacterStats> CharacterStatsReader::Read(std::string filePath, ContentManager &contentManager)
{
	auto xmlDocument = pugi::xml_document{};
	auto result = xmlDocument.load_file(filePath.c_str());

	if (!result)
	{
		FileLogger::GetInstance().Error("{}() failed: {}. Path: {}", __FUNCTION__, result.description(), filePath);
		throw LoadContentException(result.description());
	}

	auto characterNode = xmlDocument.child("GameContent").child("Character");
	auto characterStats = CharacterStats{};

	for (auto attribute : characterNode.attributes())
	{
		characterStats[attribute.name()] = attribute.value();
	}

	return std::shared_ptr<CharacterStats>(new CharacterStats(characterStats));
}
