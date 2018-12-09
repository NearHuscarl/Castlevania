#include "MapManager.h"
#include "TypeConverter.h"
#include "CppExtensions.h"

using namespace Castlevania;

MapManager::MapManager(ObjectFactory &objectFactory) : objectFactory{ objectFactory }
{
	worldPosition = Vector2::Zero();
}

void MapManager::SetWorldPosition(Vector2 position)
{
	worldPosition = position;
}

void MapManager::LoadContent(ContentManager &content)
{
	//maps[Map::INTRO] = content.Load<TiledMap>("TiledMaps/Intro.tmx");
	maps[Map::COURTYARD] = content.Load<TiledMap>("TiledMaps/Stage_01/Courtyard.tmx");
	maps[Map::GREAT_HALL] = content.Load<TiledMap>("TiledMaps/Stage_01/Great_Hall.tmx");
	maps[Map::UNDERGROUND] = content.Load<TiledMap>("TiledMaps/Stage_01/Underground.tmx");
	maps[Map::PLAYGROUND] = content.Load<TiledMap>("TiledMaps/Playground/Playground.tmx");
}

MapData MapManager::LoadMap(Map name)
{
	auto map = maps.at(name);
	auto mapObjects = map->GetMapObjects();
	
	map->SetPosition(worldPosition);

	return MapData{ map, CreateObjectCollection(mapObjects) };
}

ObjectCollection MapManager::CreateObjectCollection(ObjectsProperties objectsProperties)
{
	auto objectCollection = ObjectCollection{};

	for (auto properties : objectsProperties)
	{
		auto name = properties.at("name");
		auto type = properties.at("type");

		auto x = worldPosition.x + std::stof(properties.at("x"));
		auto y = worldPosition.y + std::stof(properties.at("y"));

		if (type == BOUNDARY) // Rectangle
		{
			auto width = std::stof(properties.at("width"));
			auto height = std::stof(properties.at("height"));
			auto bbox = RectF{ x, y, width, height };
			auto object = objectFactory.CreateBoundary(bbox);

			objectCollection.boundaries.push_back(std::move(object));
		}
		else if (type == OBJECT) // GameObject (Player, Bat, Skeleton...) // tile
		{
			auto object = ConstructObject(properties);
			auto height = std::stoi(properties.at("height"));
			auto facing = string2Facing.at(GetValueOrDefault(properties, "Facing", "Right"));
			auto foreground = GetValueOrDefault(properties, "Foreground", "False");
			auto visibility = GetValueOrDefault(properties, "Visibility", "True");

			object->SetPosition(x, y - height);
			object->SetFacing(facing);
			object->SetVisibility(ToBoolean(visibility));

			if (ToBoolean(foreground))
				objectCollection.foregroundObjects.push_back(std::move(object));
			else
				objectCollection.entities.push_back(std::move(object));
		}
		else if (type == TRIGGER) // Rectangle
		{
			auto width = std::stof(properties.at("width"));
			auto height = std::stof(properties.at("height"));
			auto bbox = RectF{ x, y, width, height };
			auto facing = string2Facing.at(GetValueOrDefault(properties, "Facing", "None"));
			auto triggerType = string2TriggerType.at(name);
			auto object = objectFactory.CreateTrigger(bbox, triggerType);

			if (triggerType == TriggerType::NEXT_MAP)
			{
				object->AddProperty("Map", properties.at("Map"));
				object->AddProperty("SpawnPoint", properties.at("SpawnPoint"));
			}

			object->Enabled(ToBoolean(properties.at("Enabled")));
			object->SetFacing(facing);
			objectCollection.triggers.push_back(std::move(object));
		}
		else if (type == SPAWNER) // Rectangle
		{
			auto width = std::stof(properties.at("width"));
			auto height = std::stof(properties.at("height"));
			auto bbox = RectF{ x, y, width, height };
			auto spawnObject = string2EntityType.at(properties.at("SpawnObject"));
			auto object = objectFactory.CreateSpawnArea(spawnObject, bbox);
			
			objectCollection.entities.push_back(std::move(object));
		}
		else if (type == POSITION)
		{
			auto height = std::stoi(properties.at("height"));
			auto position = Vector2{ x, y - height };

			objectCollection.locations[name] = position;
		}
	}

	return objectCollection;
}

std::unique_ptr<GameObject> MapManager::ConstructObject(ObjectProperties properties)
{
	auto name = properties.at("name");
	auto type = string2EntityType.at(name);

	switch (type)
	{
		case EntityType::SpawnPoint:
		{
			auto width = std::stof(properties.at("width"));
			auto height = std::stof(properties.at("height"));
			auto bbox = RectF{ 0, 0, width, height };
			auto spawnType = string2EntityType.at(properties.at("SpawnObject"));

			return objectFactory.CreateSpawnPoint(spawnType, bbox);
		}

		case EntityType::Player:
			return objectFactory.CreatePlayer();

		case EntityType::Bat:
			return objectFactory.CreateBat();

		case EntityType::Brazier:
		{
			auto itemType = string2EntityType.at(properties.at("Item"));
			return objectFactory.CreateBrazier(itemType);
		}

		case EntityType::Zombie:
			return objectFactory.CreateZombie();

		case EntityType::Panther:
			return objectFactory.CreatePanther();

		case EntityType::Dagger:
			return objectFactory.CreateDagger();

		case EntityType::MoneyBag:
			return objectFactory.CreateBat();

		case EntityType::Castle:
			return objectFactory.CreateCastle();

		case EntityType::DirtBlock:
			return objectFactory.CreateDirtBlock();

		default:
			throw std::invalid_argument("Invalid object name");
	}
}
