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
		FileLogger::GetInstance().Error(result.description());
		throw LoadContentException(result.description());
	}

	auto characterNode = xmlDocument.child("GameContent").child("Character");
	auto characterStats = CharacterStats{};

	characterStats.name = characterNode.child("Name").text().as_string();
	characterStats.speed = characterNode.child("Speed").text().as_float();
	characterStats.startingAnimation = characterNode.child("StartingAnimation").text().as_string();

	return std::shared_ptr<CharacterStats>(new CharacterStats(characterStats));
}