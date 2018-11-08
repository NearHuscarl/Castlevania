#include "Library/pugixml/pugixml.hpp"
#include "TiledMapReader.h"
#include "ContentManager.h"
#include "LoadContentException.h"
#include "../Utilities/FileLogger.h"

std::shared_ptr<TiledMap> TiledMapReader::Read(std::string path, ContentManager &contentManager)
{
	auto xmlDocument = pugi::xml_document{};
	auto result = xmlDocument.load_file(path.c_str());

	if (!result)
	{
		FileLogger::GetInstance().Error(result.description());
		throw LoadContentException(result.description());
	}

	auto mapNode = xmlDocument.child("map");

	auto name = path;
	auto mapWidth = mapNode.attribute("width").as_int();
	auto mapHeight = mapNode.attribute("height").as_int();
	auto tileWidth = mapNode.attribute("tilewidth").as_int();
	auto tileHeight = mapNode.attribute("tileheight").as_int();
	auto backgroundColor = mapNode.attribute("backgroundcolor").as_string();

	auto map = std::make_shared<TiledMap>(name, mapWidth, mapHeight, tileWidth, tileHeight, Color::FromHex(backgroundColor));
	
	// image.source store the relative path to the tmx file itself
	auto textureRelativePath = mapNode.child("imagelayer").child("image").attribute("source").as_string();
	auto texturePath = contentManager.ResolvePath(Path{ path }.parent_path(), textureRelativePath);
	auto texture = contentManager.Load<Texture>(texturePath);

	map->CreateTileSet(texture);
	map->CreateMapObjects(ReadTiledMapObjects(mapNode));

	return map;
}

TiledMapObjects TiledMapReader::ReadTiledMapObjects(pugi::xml_node mapNode)
{
	auto objects = TiledMapObjects{};

	for (auto objectGroupNode : mapNode.children("objectgroup"))
	{
		for (auto objectNode : objectGroupNode.children("object"))
		{
			auto objectProperties = TiledMapObjectProperties{};

			for (auto attribute : objectNode.attributes())
			{
				objectProperties[attribute.name()] = attribute.value();
			}
			objects.push_back(objectProperties);
		}
	}

	return objects;
}
