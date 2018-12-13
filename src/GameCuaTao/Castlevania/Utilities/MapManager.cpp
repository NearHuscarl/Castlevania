#include "MapManager.h"
#include "TypeConverter.h"
#include "CppExtensions.h"

using namespace Castlevania;

constexpr auto BOUND = "Bounds";
constexpr auto TRIGGER = "Triggers";
constexpr auto LOCATION = "Locations";
constexpr auto FOREGROUND = "Foregrounds";
constexpr auto ENTITY = "Entities";
constexpr auto AREA = "Areas";

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

std::shared_ptr<TiledMap> MapManager::GetTiledMap(Map name)
{
	auto map = maps.at(name);
	map->SetPosition(worldPosition);

	return map;
}

ObjectCollection MapManager::GetOtherObjects(Map name)
{
	auto map = maps.at(name);
	auto mapObjects = map->GetMapObjects();

	return CreateObjectCollection(mapObjects);
}

GameObjects MapManager::GetMapObjects(Map name)
{
	return GetMapObjectsInArea(name, Rect::Empty());
}

GameObjects MapManager::GetMapObjectsInArea(Map name, Rect area)
{
	auto map = maps.at(name);
	auto objectGroups = map->GetMapObjects();
	auto x = float{};
	auto y = float{};
	auto objects = GameObjects{};

	for (auto properties : objectGroups[ENTITY])
	{
		ReadObjectPosition(properties, x, y);
		auto height = std::stoi(properties.at("height"));
		auto position = Vector2{ x, y - height };

		if (!area.Contains(position) && area != Rect::Empty())
			continue;

		auto object = ConstructObject(properties);
		auto facing = string2Facing.at(GetValueOrDefault(properties, "Facing", "Right"));

		object->SetPosition(position);
		object->SetFacing(facing);

		objects.push_back(std::move(object));
	}

	for (auto properties : objectGroups[AREA])
	{
		auto typeName = properties.at("type");
		auto type = string2EntityType.at(typeName);

		if (type != EntityType::SpawnArea)
			continue;

		ReadObjectPosition(properties, x, y);
		auto width = std::stof(properties.at("width"));
		auto height = std::stof(properties.at("height"));
		auto bbox = RectF{ x, y, width, height };

		if (!area.Contains((Rect)bbox) && area != Rect::Empty())
			continue;

		auto spawnObject = string2EntityType.at(properties.at("SpawnObject"));
		auto object = objectFactory.CreateSpawnArea(spawnObject, bbox);

		auto spawnGroup = GetValueOrDefault(properties, "SpawnGroup", "");

		if (!spawnGroup.empty())
			object->SetGroupCountChances(spawnGroup);

		auto spawnDirection = GetValueOrDefault(properties, "SpawnDirection", "");

		if (!spawnDirection.empty())
			object->SetDirectionChances(spawnDirection);

		objects.push_back(std::move(object));
	}

	return objects;
}

ObjectCollection MapManager::CreateObjectCollection(TiledMapObjectGroups objectGroups)
{
	auto objectCollection = ObjectCollection{};
	auto x = float{};
	auto y = float{};

	for (auto properties : objectGroups[LOCATION])
	{
		ReadObjectPosition(properties, x, y);
		auto height = std::stoi(properties.at("height"));
		auto position = Vector2{ x, y - height };
		auto name = properties.at("name");

		objectCollection.locations[name] = position;
	}

	for (auto properties : objectGroups[TRIGGER])
	{
		ReadObjectPosition(properties, x, y);
		auto width = std::stof(properties.at("width"));
		auto height = std::stof(properties.at("height"));
		auto bbox = RectF{ x, y, width, height };
		auto facing = string2Facing.at(GetValueOrDefault(properties, "Facing", "None"));
		auto name = properties.at("name");
		auto triggerType = string2TriggerType.at(name);
		auto object = objectFactory.CreateTrigger(bbox, triggerType);

		if (triggerType == TriggerType::NEXT_MAP)
		{
			object->AddProperty("Map", properties.at("Map"));
			object->AddProperty("SpawnPoint", GetValueOrDefault(properties, "SpawnPoint", "Checkpoint"));
		}

		object->Enabled(ToBoolean(properties.at("Enabled")));
		object->SetFacing(facing);
		objectCollection.triggers.push_back(std::move(object));
	}

	for (auto properties : objectGroups[FOREGROUND])
	{
		ReadObjectPosition(properties, x, y);
		auto height = std::stoi(properties.at("height"));
		auto position = Vector2{ x, y - height };
		auto object = ConstructObject(properties);
		auto facing = string2Facing.at(GetValueOrDefault(properties, "Facing", "Right"));
		auto visibility = GetValueOrDefault(properties, "Visibility", "True");

		object->SetPosition(position);
		object->SetFacing(facing);
		object->SetVisibility(ToBoolean(visibility));

		objectCollection.foregroundObjects.push_back(std::move(object));
	}

	for (auto properties : objectGroups[BOUND])
	{
		ReadObjectPosition(properties, x, y);
		auto width = std::stof(properties.at("width"));
		auto height = std::stof(properties.at("height"));
		auto bbox = RectF{ x, y, width, height };
		auto object = objectFactory.CreateBoundary(bbox);

		objectCollection.boundaries.push_back(std::move(object));
	}

	for (auto properties : objectGroups[AREA])
	{
		auto typeName = properties.at("type");
		auto type = string2EntityType.at(typeName);

		if (type != EntityType::ViewportArea)
			continue;

		ReadObjectPosition(properties, x, y);
		auto width = std::stof(properties.at("width"));
		auto height = std::stof(properties.at("height"));
		auto bbox = RectF{ x, y, width, height };
		auto object = objectFactory.CreateViewportArea(bbox);

		objectCollection.viewportAreas.push_back(std::move(object));
	}

	return objectCollection;
}

std::unique_ptr<GameObject> MapManager::ConstructObject(ObjectProperties properties)
{
	auto typeName = properties.at("type");
	auto type = string2EntityType.at(typeName);

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

		case EntityType::Candle:
		{
			auto itemType = string2EntityType.at(properties.at("Item"));
			return objectFactory.CreateCandle(itemType);
		}

		case EntityType::Zombie:
			return objectFactory.CreateZombie();

		case EntityType::Panther:
			return objectFactory.CreatePanther();

		case EntityType::Dagger:
			return objectFactory.CreateDagger();

		case EntityType::BlueMoneyBag:
			return objectFactory.CreateBlueMoneyBag();

		case EntityType::WhiteMoneyBag:
			return objectFactory.CreateWhiteMoneyBag();

		case EntityType::RedMoneyBag:
			return objectFactory.CreateRedMoneyBag();

		case EntityType::Door:
			return objectFactory.CreateDoor();

		case EntityType::Castle:
			return objectFactory.CreateCastle();

		case EntityType::DirtBlock:
			return objectFactory.CreateDirtBlock();

		default:
			throw std::invalid_argument("Invalid object name");
	}
}

void MapManager::ReadObjectPosition(ObjectProperties properties, float &x, float &y)
{
	x = worldPosition.x + std::stof(properties.at("x"));
	y = worldPosition.y + std::stof(properties.at("y"));
}
