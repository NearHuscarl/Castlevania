#include "TiledMapReader.h"
#include "ContentManager.h"
#include "LoadContentException.h"
#include "../Utilities/FileLogger.h"

std::shared_ptr<TiledMap> TiledMapReader::Read(std::string filePath, ContentManager &contentManager)
{
	auto xmlDocument = pugi::xml_document{};
	auto result = xmlDocument.load_file(filePath.c_str());

	if (!result)
	{
		FileLogger::GetInstance().Error("{}() failed: {}. Path: {}", __FUNCTION__, result.description(), filePath);
		throw LoadContentException(result.description());
	}

	auto mapNode = xmlDocument.child("map");

	auto name = filePath;
	auto mapWidth = mapNode.attribute("width").as_int();
	auto mapHeight = mapNode.attribute("height").as_int();
	auto tileWidth = mapNode.attribute("tilewidth").as_int();
	auto tileHeight = mapNode.attribute("tileheight").as_int();
	auto backgroundColor = mapNode.attribute("backgroundcolor").as_string();

	auto map = std::make_shared<TiledMap>(name, mapWidth, mapHeight, tileWidth, tileHeight, Color::FromHex(backgroundColor));
	
	// image.source store the relative path to the tmx file itself
	auto texturePath = mapNode.child("imagelayer").child("image").attribute("source").as_string();
	auto resolvedTexturePath = contentManager.ResolvePath(Path{ filePath }.parent_path(), texturePath);
	auto texture = contentManager.Load<Texture>(resolvedTexturePath);

	map->CreateTileSet(texture);
	map->CreateMapObjects(ReadTiledMapObjects(mapNode));

	return map;
}

TiledMapObjectGroups TiledMapReader::ReadTiledMapObjects(pugi::xml_node mapNode)
{
	auto objectGroups = TiledMapObjectGroups{};

	for (auto objectGroupNode : mapNode.children("objectgroup"))
	{
		auto objects = TiledMapObjects{};

		for (auto objectNode : objectGroupNode.children("object"))
		{
			auto objectProperties = TiledMapObjectProperties{};

			for (auto attribute : objectNode.attributes())
			{
				objectProperties[attribute.name()] = attribute.value();
			}

			// Read object's custom properties
			for (auto property : objectNode.child("properties").children("property"))
			{
				auto name = property.attribute("name").as_string();
				auto value = property.attribute("value").as_string();

				objectProperties[name] = value;
			}

			objects.push_back(objectProperties);
		}

		auto groupName = objectGroupNode.attribute("name").as_string();

		objectGroups[groupName] = objects;
	}

	return objectGroups;
}
