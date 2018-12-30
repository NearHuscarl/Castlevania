#include "TiledMapReader.h"
#include "ContentManager.h"
#include "LoadContentException.h"
#include "../GraphicsDeviceManager.h"
#include "../Utilities/CppExtensions.h"
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

	auto map = std::make_shared<TiledMap>(name, mapWidth, mapHeight, tileWidth, tileHeight);

	auto useTileLayer = false;
	auto tileLayerId = int{};
	auto tileLayerTexture = std::string{};

	for (auto tileSetNode : mapNode.children("tileset"))
	{
		auto imagePath = tileSetNode.child("image").attribute("source").as_string();

		if (EndsWith(imagePath, ".bmp")) // Our map tileset will be stored in bitmap
		{
			tileLayerId = tileSetNode.attribute("firstgid").as_int();
			tileLayerTexture = tileSetNode.child("image").attribute("source").as_string();
			useTileLayer = true;
			break;
		}
	}

	if (useTileLayer)
	{
		auto layerDataNode = mapNode.child("layer").child("data");
		auto graphics = contentManager.GetServiceProvider().Get<GraphicsDeviceManager>();
		auto &graphicsDevice = graphics->GetGraphicsDevice();
		auto oldColorKey = graphicsDevice.GetColorKey();
		auto colorKey = mapNode.child("layer").child("properties").child("property").attribute("value").as_string();
		auto resolvedTexturePath = contentManager.ResolvePath(Path{ filePath }.parent_path(), tileLayerTexture);
		
		graphicsDevice.SetColorKey(Color::FromArgb(colorKey));
		auto tileSetTexture = contentManager.Load<Texture>(resolvedTexturePath);
		graphicsDevice.SetColorKey(oldColorKey);

		auto csvTileSetData = mapNode.child("layer").child("data").text().as_string();
		auto tileSetData = Split(csvTileSetData, ',');

		map->SetTileLayer(ReadTileLayer(tileLayerId, tileSetTexture, tileSetData, tileWidth, tileHeight, mapWidth));
	}
	else
	{
		// image.source store the relative path to the tmx file itself
		auto texturePath = mapNode.child("imagelayer").child("image").attribute("source").as_string();
		auto resolvedTexturePath = contentManager.ResolvePath(Path{ filePath }.parent_path(), texturePath);
		auto imageTexture = contentManager.Load<Texture>(resolvedTexturePath);

		map->SetTileLayer(ReadImageLayer(imageTexture, tileWidth, tileHeight, mapWidth, mapHeight));
	}

	map->SetMapObjects(ReadTiledMapObjects(mapNode));

	return map;
}

std::unique_ptr<TileSet> TiledMapReader::ReadImageLayer(
	std::shared_ptr<Texture> tileSetTexture,
	int tileWidth,
	int tileHeight,
	int width,
	int height)
{
	auto texture = tileSetTexture;
	auto tiles = std::make_unique<TileSet>();
	auto rows = height;
	auto columns = width;

	for (auto row = 0; row < rows; row++)
	{
		tiles->push_back(std::vector<Tile>{}); // Add new row

		for (auto column = 0; column < columns; column++)
		{
			auto rect = Rect{
				tileWidth * column,
				tileHeight * row,
				tileWidth,
				tileHeight,
			};

			auto textureRegion = TextureRegion{ texture, rect };
			(*tiles)[row].push_back(Tile{ textureRegion, rect });
		}
	}

	return tiles;
}

std::unique_ptr<TileSet> TiledMapReader::ReadTileLayer(
	int tileLayerId,
	std::shared_ptr<Texture> tileSetTexture,
	std::vector<std::string> tileSetData,
	int tileWidth,
	int tileHeight,
	int width)
{
	auto tileSetColumn = tileSetTexture->Width() / tileWidth;
	auto tiles = std::make_unique<TileSet>();
	auto column = 0;
	auto row = 0;

	tiles->push_back(std::vector<Tile>{}); // Add new row

	for (auto tileData : tileSetData)
	{
		auto tileId = std::stoi(tileData) - tileLayerId;
		auto rect = Rect{
			tileWidth * (tileId % tileSetColumn),
			tileHeight * (tileId / tileSetColumn),
			tileWidth,
			tileHeight };
		auto tileRegion = TextureRegion{ tileSetTexture, rect };
		auto tileSprite = Sprite{ tileRegion };
		auto tileBbox = Rect{
			tileWidth * column,
			tileHeight * row,
			tileWidth,
			tileHeight };

		(*tiles)[row].push_back(Tile{ tileSprite, tileBbox });
		column = ++column % width;

		if (column == 0)
		{
			tiles->push_back(std::vector<Tile>{});
			row++;
		}
	}

	return tiles;
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
