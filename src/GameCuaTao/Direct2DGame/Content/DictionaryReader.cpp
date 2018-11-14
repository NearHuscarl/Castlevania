#include "Library/pugixml/pugixml.hpp"
#include "DictionaryReader.h"
#include "LoadContentException.h"
#include "../Utilities/FileLogger.h"

std::shared_ptr<Dictionary> DictionaryReader::Read(std::string filePath, ContentManager &contentManager)
{
	auto xmlDocument = pugi::xml_document{};
	auto result = xmlDocument.load_file(filePath.c_str());

	if (!result)
	{
		FileLogger::GetInstance().Error("{}() failed: {}. Path: {}", __FUNCTION__, result.description(), filePath);
		throw LoadContentException(result.description());
	}

	auto dictionaryNode = xmlDocument.child("GameContent").child("Dictionary");
	auto dict = Dictionary{};

	for (auto attribute : dictionaryNode.attributes())
	{
		dict[attribute.name()] = attribute.value();
	}

	return std::shared_ptr<Dictionary>(new Dictionary(dict));
}
