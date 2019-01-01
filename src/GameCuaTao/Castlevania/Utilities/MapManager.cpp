#include "Direct2DGame/Utilities/CppExtensions.h"
#include "MapManager.h"
#include "TypeConverter.h"
#include "../Scenes/Stages/StageObject.h"

using namespace Castlevania;

constexpr auto BOUND = "Bounds";
constexpr auto TRIGGER = "Triggers";
constexpr auto LOCATION = "Locations";
constexpr auto FOREGROUND = "Foregrounds";
constexpr auto ENTITY = "Entities";
constexpr auto AREA = "Areas";

MapManager::MapManager(ContentManager &content, ObjectFactory &objectFactory) :
	content{ content },
	objectFactory{ objectFactory }
{
	worldPosition = Vector2::Zero();

	maps[Map::INTRO] = "TiledMaps/Intro/Intro.tmx";
	maps[Map::COURTYARD] = "TiledMaps/Stage_01/Courtyard.tmx";
	maps[Map::GREAT_HALL] = "TiledMaps/Stage_01/Great_Hall.tmx";
	maps[Map::UNDERGROUND] = "TiledMaps/Stage_01/Underground.tmx";
	maps[Map::PLAYGROUND] = "TiledMaps/Playground/Playground.tmx";
}

void MapManager::SetWorldPosition(Vector2 position)
{
	worldPosition = position;
}

std::shared_ptr<TiledMap> MapManager::GetTiledMap(Map name)
{
	auto map = content.Load<TiledMap>(maps.at(name));
	map->SetPosition(worldPosition);

	return map;
}

std::unique_ptr<StageObject> MapManager::GetStageObjects(Map name)
{
	auto objectGroups = GetTiledMap(name)->GetMapObjects();
	auto stageObject = std::make_unique<StageObject>();

	GetLocations(stageObject->locations, objectGroups);
	GetStageAreas(stageObject->stageAreas, objectGroups);

	return stageObject;
}

ObjectCollection MapManager::GetMapObjects(Map name)
{
	return GetMapObjectsInArea(name, Rect::Empty());
}

ObjectCollection MapManager::GetMapObjectsInArea(Map name, RectF area)
{
	auto objectGroups = GetTiledMap(name)->GetMapObjects();
	auto objectCollection = ObjectCollection{};

	GetTriggers(objectCollection.staticObjects, objectGroups, area);
	GetEntities(objectCollection.entities, objectGroups, area);
	GetBounds(objectCollection.blocks, objectGroups, area);

	return objectCollection;
}

std::unique_ptr<GameObject> MapManager::ConstructObject(ObjectProperties properties)
{
	auto typeName = properties.at("type");
	auto type = string2EntityType.at(typeName);

	switch (type)
	{
		case ObjectId::Player:
			return objectFactory.CreatePlayer();

		case ObjectId::SpawnPoint:
		{
			auto width = std::stof(properties.at("width"));
			auto height = std::stof(properties.at("height"));
			auto bbox = RectF{ 0, 0, width, height };
			auto spawnType = string2EntityType.at(properties.at("SpawnObject"));

			return objectFactory.CreateSpawnPoint(spawnType, bbox);
		}

		case ObjectId::WaterArea:
		{
			auto width = std::stof(properties.at("width"));
			auto height = std::stof(properties.at("height"));
			auto bbox = RectF{ 0, 0, width, height };

			return objectFactory.CreateWaterArea(bbox);
		}

		case ObjectId::Bat:
			return objectFactory.CreateBat();

		case ObjectId::Cloud:
			return objectFactory.CreateCloud();

		case ObjectId::Brazier:
		{
			auto itemType = string2EntityType.at(properties.at("Item"));
			return objectFactory.CreateBrazier(itemType);
		}

		case ObjectId::Candle:
		{
			auto itemType = string2EntityType.at(properties.at("Item"));
			return objectFactory.CreateCandle(itemType);
		}

		case ObjectId::BreakableBlock:
		{
			auto itemType = string2EntityType.at(properties.at("Item"));
			return objectFactory.CreateBreakableBlock(itemType);
		}

		case ObjectId::BreakableWall:
		{
			auto itemType = string2EntityType.at(properties.at("Item"));
			return objectFactory.CreateBreakableWall(itemType);
		}

		case ObjectId::Zombie:
			return objectFactory.CreateZombie();

		case ObjectId::Panther:
			return objectFactory.CreatePanther();

		case ObjectId::GiantBat:
			return objectFactory.CreateGiantBat();

		case ObjectId::Dagger:
			return objectFactory.CreateDagger();

		case ObjectId::BlueMoneyBag:
			return objectFactory.CreateBlueMoneyBag();

		case ObjectId::WhiteMoneyBag:
			return objectFactory.CreateWhiteMoneyBag();

		case ObjectId::RedMoneyBag:
			return objectFactory.CreateRedMoneyBag();

		case ObjectId::FlashingMoneyBag:
			return objectFactory.CreateFlashingMoneyBag();

		case ObjectId::Door:
			return objectFactory.CreateDoor();

		case ObjectId::Castle:
			return objectFactory.CreateCastle();

		case ObjectId::BrickBlock:
			return objectFactory.CreateBrickBlock();

		case ObjectId::DirtBlock:
			return objectFactory.CreateDirtBlock();

		default:
			throw std::invalid_argument("Invalid object name");
	}
}

RectF MapManager::GetMapObjectBoundingBox(ObjectProperties properties, MapObjectType type)
{
	auto x = worldPosition.x + std::stof(properties.at("x"));
	auto y = worldPosition.y + std::stof(properties.at("y"));
	auto width = std::stof(properties.at("width"));
	auto height = std::stof(properties.at("height"));

	if (type == MapObjectType::Tile)
		return RectF{ x, y - height, width, height };
	else // (type == MapObjectType::Rectangle)
		return RectF{ x, y, width, height };
}

void MapManager::GetLocations(std::map<std::string, Checkpoint> &objects, TiledMapObjectGroups &objectGroups)
{
	for (auto properties : objectGroups[LOCATION])
	{
		auto boundingBox = GetMapObjectBoundingBox(properties, MapObjectType::Tile);
		auto name = properties.at("name");
		auto position = Vector2{ boundingBox.X(), boundingBox.Y() };
		auto facing = string2Facing.at(GetValueOrDefault(properties, "Facing", "None"));

		objects[name] = Checkpoint{ position, facing };
	}
}

void MapManager::GetStageAreas(std::vector<std::unique_ptr<GameObject>> &objects, TiledMapObjectGroups &objectGroups)
{
	for (auto properties : objectGroups[AREA])
	{
		auto typeName = properties.at("type");
		auto type = string2EntityType.at(typeName);

		if (type != ObjectId::StageArea)
			continue;

		auto boundingBox = GetMapObjectBoundingBox(properties, MapObjectType::Rectangle);
		auto object = objectFactory.CreateRectangleObject(type, boundingBox);
		objects.push_back(std::move(object));
	}
}

void MapManager::GetTriggers(std::vector<std::unique_ptr<GameObject>> &objects, TiledMapObjectGroups &objectGroups, RectF area)
{
	for (auto properties : objectGroups[TRIGGER])
	{
		auto boundingBox = GetMapObjectBoundingBox(properties, MapObjectType::Rectangle);
		auto position = Vector2{ boundingBox.left, boundingBox.top };
		if (!area.Contains(position) && area != RectF::Empty())
			continue;

		auto facing = string2Facing.at(GetValueOrDefault(properties, "Facing", "None"));
		auto name = properties.at("name");
		auto triggerType = string2TriggerType.at(name);
		auto object = objectFactory.CreateTrigger(boundingBox, triggerType);

		if (triggerType == TriggerType::NEXT_MAP)
		{
			object->AddProperty("Map", properties.at("Map"));
			object->AddProperty("SpawnPoint", GetValueOrDefault(properties, "SpawnPoint", "Checkpoint"));
		}

		object->GetBody().Enabled(ToBoolean(properties.at("Enabled")));
		object->SetFacing(facing);
		objects.push_back(std::move(object));
	}
}

void MapManager::GetEntities(std::vector<std::unique_ptr<GameObject>> &objects, TiledMapObjectGroups &objectGroups, RectF area)
{
	for (auto properties : objectGroups[ENTITY])
	{
		auto boundingBox = GetMapObjectBoundingBox(properties, MapObjectType::Tile);
		auto position = Vector2{ boundingBox.X(), boundingBox.Y() };
		if (!area.Contains(position) && area != RectF::Empty())
			continue;

		auto object = ConstructObject(properties);
		auto facing = string2Facing.at(GetValueOrDefault(properties, "Facing", "Right"));
		auto speed = std::stof(GetValueOrDefault(properties, "Speed", "-1"));
		auto direction = std::stof(GetValueOrDefault(properties, "Direction", "-1"));

		if (speed != -1)
			object->SetSpeed(speed);

		if (direction != -1)
			object->SetDirection(direction);

		object->SetPosition(position);
		object->SetFacing(facing);

		objects.push_back(std::move(object));
	}
}

void MapManager::GetBounds(std::vector<std::unique_ptr<GameObject>> &objects, TiledMapObjectGroups &objectGroups, RectF area)
{
	for (auto properties : objectGroups[BOUND])
	{
		auto boundingBox = GetMapObjectBoundingBox(properties, MapObjectType::Rectangle);
		if (!area.TouchesOrIntersects(boundingBox) && area != RectF::Empty())
			continue;

		auto object = objectFactory.CreateBoundary(boundingBox);

		objects.push_back(std::move(object));
	}
}

void MapManager::GetAreas(std::vector<std::unique_ptr<GameObject>> &objects, TiledMapObjectGroups &objectGroups, RectF area)
{
	for (auto properties : objectGroups[AREA])
	{
		auto typeName = properties.at("type");
		auto type = string2EntityType.at(typeName);
		auto boundingBox = GetMapObjectBoundingBox(properties, MapObjectType::Rectangle);
		auto position = Vector2{ boundingBox.X(), boundingBox.Y() };

		if (!area.Contains(position) && area != Rect::Empty())
			continue;

		switch (type)
		{
			case ObjectId::SpawnArea:
			{
				auto spawnObject = string2EntityType.at(properties.at("SpawnObject"));
				auto object = objectFactory.CreateSpawnArea(spawnObject, boundingBox);

				auto spawnGroup = GetValueOrDefault(properties, "SpawnGroup", "");

				if (!spawnGroup.empty())
					object->SetGroupCountChances(spawnGroup);

				auto spawnDirection = GetValueOrDefault(properties, "SpawnDirection", "");

				if (!spawnDirection.empty())
					object->SetDirectionChances(spawnDirection);

				objects.push_back(std::move(object));
				break;
			}

			// Dump area objects that dont have Update() method
			case ObjectId::BossFightArea:
			{
				auto object = objectFactory.CreateRectangleObject(type, boundingBox);
				objects.push_back(std::move(object));
				break;
			}
		}
	}
}

void MapManager::GetForegrounds(std::vector<std::unique_ptr<GameObject>> &objects, TiledMapObjectGroups &objectGroups, RectF area)
{
	for (auto properties : objectGroups[FOREGROUND])
	{
		auto boundingBox = GetMapObjectBoundingBox(properties, MapObjectType::Tile);
		auto position = Vector2{ boundingBox.X(), boundingBox.Y() };
		if (!area.Contains(position) && area != RectF::Empty())
			continue;

		auto object = ConstructObject(properties);
		auto facing = string2Facing.at(GetValueOrDefault(properties, "Facing", "Right"));
		auto visibility = GetValueOrDefault(properties, "Visibility", "True");

		object->SetPosition(position);
		object->SetFacing(facing);
		object->SetVisibility(ToBoolean(visibility));

		objects.push_back(std::move(object));
	}
}
