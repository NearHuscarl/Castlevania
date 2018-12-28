#include "MapManager.h"
#include "TypeConverter.h"
#include "CppExtensions.h"
#include "../Scenes/Stages/StageObject.h"

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

void MapManager::LoadContent(ContentManager &content)
{
	maps[Map::INTRO] = content.Load<TiledMap>("TiledMaps/Intro/Intro.tmx");
	maps[Map::COURTYARD] = content.Load<TiledMap>("TiledMaps/Stage_01/Courtyard.tmx");
	maps[Map::GREAT_HALL] = content.Load<TiledMap>("TiledMaps/Stage_01/Great_Hall.tmx");
	maps[Map::UNDERGROUND] = content.Load<TiledMap>("TiledMaps/Stage_01/Underground.tmx");
	maps[Map::PLAYGROUND] = content.Load<TiledMap>("TiledMaps/Playground/Playground.tmx");
}

void MapManager::SetWorldPosition(Vector2 position)
{
	worldPosition = position;
}

std::shared_ptr<TiledMap> MapManager::GetTiledMap(Map name)
{
	auto map = maps.at(name);
	map->SetPosition(worldPosition);

	return map;
}

std::unique_ptr<StageObject> MapManager::GetStageObjects(Map name)
{
	auto map = maps.at(name);
	auto objectGroups = map->GetMapObjects();
	auto stageObject = std::make_unique<StageObject>();

	for (auto properties : objectGroups[LOCATION])
	{
		auto boundingBox = GetMapObjectBoundingBox(properties, MapObjectType::Tile);
		auto name = properties.at("name");
		auto position = Vector2{ boundingBox.X(), boundingBox.Y() };

		stageObject->locations[name] = position;
	}

	for (auto properties : objectGroups[AREA])
	{
		auto typeName = properties.at("type");
		auto type = string2EntityType.at(typeName);

		auto boundingBox = GetMapObjectBoundingBox(properties, MapObjectType::Rectangle);

		if (type == ObjectId::StageArea)
		{
			auto object = objectFactory.CreateRectangleObject(type, boundingBox);
			stageObject->stageAreas.push_back(std::move(object));
		}
		else if (type == ObjectId::SpawnArea)
		{
			auto spawnObject = string2EntityType.at(properties.at("SpawnObject"));
			auto object = objectFactory.CreateSpawnArea(spawnObject, boundingBox);

			auto spawnGroup = GetValueOrDefault(properties, "SpawnGroup", "");

			if (!spawnGroup.empty())
				object->SetGroupCountChances(spawnGroup);

			auto spawnDirection = GetValueOrDefault(properties, "SpawnDirection", "");

			if (!spawnDirection.empty())
				object->SetDirectionChances(spawnDirection);

			stageObject->spawnAreas.push_back(std::move(object));
		}
	}

	for (auto properties : objectGroups[FOREGROUND])
	{
		auto boundingBox = GetMapObjectBoundingBox(properties, MapObjectType::Tile);
		auto object = ConstructObject(properties);
		auto facing = string2Facing.at(GetValueOrDefault(properties, "Facing", "Right"));
		auto visibility = GetValueOrDefault(properties, "Visibility", "True");
		auto position = Vector2{ boundingBox.X(), boundingBox.Y() };

		object->SetPosition(position);
		object->SetFacing(facing);
		object->SetVisibility(ToBoolean(visibility));

		stageObject->foregroundObjects.push_back(std::move(object));
	}

	return stageObject;
}

ObjectCollection MapManager::GetMapObjects(Map name)
{
	return GetMapObjectsInArea(name, Rect::Empty());
}

ObjectCollection MapManager::GetMapObjectsInArea(Map name, RectF area)
{
	auto map = maps.at(name);
	auto objectGroups = map->GetMapObjects();
	auto objectCollection = ObjectCollection{};

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
		objectCollection.staticObjects.push_back(std::move(object));
	}

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

		objectCollection.entities.push_back(std::move(object));
	}

	for (auto properties : objectGroups[BOUND])
	{
		auto boundingBox = GetMapObjectBoundingBox(properties, MapObjectType::Rectangle);
		if (!area.TouchesOrIntersects(boundingBox) && area != RectF::Empty())
			continue;

		auto object = objectFactory.CreateBoundary(boundingBox);

		objectCollection.blocks.push_back(std::move(object));
	}

	for (auto properties : objectGroups[AREA])
	{
		auto typeName = properties.at("type");
		auto type = string2EntityType.at(typeName);
		auto boundingBox = GetMapObjectBoundingBox(properties, MapObjectType::Rectangle);
		auto position = Vector2{ boundingBox.X(), boundingBox.Y() };

		if (!area.Contains(position) && area != Rect::Empty())
			continue;

		auto object = std::unique_ptr<GameObject>{};

		switch (type)
		{
			case ObjectId::WaterArea:
				object = objectFactory.CreateWaterArea(boundingBox);
				objectCollection.entities.push_back(std::move(object));
				break;


			// Dump area objects that dont have Update() method
			case ObjectId::StageArea:
			case ObjectId::SpawnArea:
				break;

			default: // ObjectId::BossFightArea
				object = objectFactory.CreateRectangleObject(type, boundingBox);
				objectCollection.staticObjects.push_back(std::move(object));
				break;
		}
	}

	return objectCollection;
}

std::unique_ptr<GameObject> MapManager::ConstructObject(ObjectProperties properties)
{
	auto typeName = properties.at("type");
	auto type = string2EntityType.at(typeName);

	switch (type)
	{
		case ObjectId::SpawnPoint:
		{
			auto width = std::stof(properties.at("width"));
			auto height = std::stof(properties.at("height"));
			auto bbox = RectF{ 0, 0, width, height };
			auto spawnType = string2EntityType.at(properties.at("SpawnObject"));

			return objectFactory.CreateSpawnPoint(spawnType, bbox);
		}

		case ObjectId::Player:
			return objectFactory.CreatePlayer();

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
