#include "StageManager.h"
#include "../Utilities/CppExtensions.h"

using namespace Castlevania;

const auto string2EntityType = std::unordered_map<std::string, EntityType>
{
	{ "Player", EntityType::Player },
	{ "Bat", EntityType::Bat },
	{ "Cloud", EntityType::Cloud },
	{ "FirePit", EntityType::FirePit },
	{ "Whip", EntityType::Whip },
	{ "KnifeItem", EntityType::KnifeItem },
	{ "Heart", EntityType::Heart },
	{ "WhipPowerup", EntityType::WhipPowerup },
	{ "MoneyBag", EntityType::MoneyBag },
};

const auto string2TriggerType = std::unordered_map<std::string, TriggerType>
{
	{ "NextMap", TriggerType::NEXT_MAP },
	{ "MoneyBagTrigger", TriggerType::MONEY_BAG_EASTER_EGG },
	{ "StairUp", TriggerType::STAIR_UP },
	{ "StairDown", TriggerType::STAIR_DOWN },
};

const auto string2Facing = std::unordered_map<std::string, Facing>
{
	{ "Left", Facing::Left },
	{ "Right", Facing::Right },
	{ "None", Facing::None },
};

StageManager::StageManager(ObjectFactory &objectFactory) : objectFactory{ objectFactory }
{
	worldPosition = Vector2::Zero();
}

void StageManager::SetWorldPosition(Vector2 position)
{
	worldPosition = position;
}

void StageManager::LoadContent(ContentManager &content)
{
	//maps[Map::INTRO] = content.Load<TiledMap>("TiledMaps/Intro.tmx");
	maps[Map::STAGE_01_COURTYARD] = content.Load<TiledMap>("TiledMaps/Stage_01/Courtyard.tmx");
	//maps[Map::STAGE_01_GREAT_HALL] = content.Load<TiledMap>("TiledMaps/Stage_01/Great_Hall.tmx");
	//maps[Map::STAGE_01_UNDERGROUND] = content.Load<TiledMap>("TiledMaps/Stage_01/Underground.tmx");
	maps[Map::PLAYGROUND] = content.Load<TiledMap>("TiledMaps/Playground/Playground.tmx");
}

std::shared_ptr<TiledMap> StageManager::NextMap(Map name)
{
	currentMap = maps.at(name);
	currentMap->SetPosition(worldPosition);

	return currentMap;
}

ObjectCollection StageManager::LoadGameObjects()
{
	auto mapObjects = currentMap->GetMapObjects();

	return CreateObjectCollection(mapObjects);
}

ObjectCollection StageManager::CreateObjectCollection(ObjectsProperties objectsProperties)
{
	auto objectCollection = ObjectCollection{};

	for (auto properties : objectsProperties)
	{
		auto name = properties.at("name");
		auto type = properties.at("type");

		auto x = worldPosition.x + std::stof(properties.at("x"));
		auto y = worldPosition.y + std::stof(properties.at("y"));

		if (type == BOUNDARY) // rectangle
		{
			auto width = std::stof(properties.at("width"));
			auto height = std::stof(properties.at("height"));
			auto bbox = RectF{ x, y, width, height };
			auto object = std::make_unique<RectangleObject>(bbox);

			objectCollection.boundaries.push_back(std::move(object));
		}
		else if (type == TRIGGER) // rectangle
		{
			auto width = std::stof(properties.at("width"));
			auto height = std::stof(properties.at("height"));
			auto bbox = RectF{ x, y, width, height };
			auto facing = string2Facing.at(GetValueOrDefault(properties, "Facing", "None"));
			auto triggerType = string2TriggerType.at(name);
			auto object = std::make_unique<Trigger>(bbox, triggerType);
			
			object->SetFacing(facing);
			objectCollection.triggers.push_back(std::move(object));
		}
		else if (type == POSITION)
		{
			auto height = std::stoi(properties.at("height"));
			auto position = Vector2{ x, y - height };

			objectCollection.locations[name] = position;
		}
		else if (type == OBJECT) // GameObject (Player, Bat, Skeleton...) // tile
		{
			auto object = ConstructObject(properties);
			auto height = std::stoi(properties.at("height"));

			object->SetPosition(x, y - height);
			objectCollection.entities.push_back(std::move(object));
		}
	}

	return objectCollection;
}

std::unique_ptr<GameObject> StageManager::ConstructObject(ObjectProperties properties)
{
	auto name = properties.at("name");
	auto type = string2EntityType.at(name);

	switch (type)
	{
		case EntityType::Player:
			return objectFactory.CreatePlayer();

		case EntityType::Bat:
			return objectFactory.CreateBat();

		case EntityType::FirePit:
		{
			auto itemType = string2EntityType.at(properties.at("Item"));
			return objectFactory.CreateFirePit(itemType);
		}

		case EntityType::Knife:
			return objectFactory.CreateKnife();

		case EntityType::MoneyBag:
			return objectFactory.CreateBat();

		default:
			throw std::invalid_argument("Invalid object name");
	}
}
