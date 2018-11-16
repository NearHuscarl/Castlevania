#include "ObjectFactory.h"
#include "../Models/GameObject.h"
#include "../Models/Characters/Player/Controller.h"
#include "../Models/Characters/Bat.h"
#include "../Models/Items/FirePit.h"

using namespace Castlevania;

ObjectFactory::ObjectFactory()
{
	stringToType =
	{
		{ "Player", EntityType::Player },
		{ "Bat", EntityType::Bat },
		{ "Cloud", EntityType::Cloud },
		{ "FirePit", EntityType::FirePit },
	};
}

ObjectCollection ObjectFactory::CreateObjectCollection(ObjectsProperties objectsProperties)
{
	auto objectCollection = ObjectCollection{};

	for (auto properties : objectsProperties)
	{
		auto name = properties.at("name");

		if (BOUNDARIES.find(name) != BOUNDARIES.end()) // rectangle
		{
			auto x = std::stoi(properties.at("x"));
			auto y = std::stoi(properties.at("y"));
			auto width = std::stoi(properties.at("width"));
			auto height = std::stoi(properties.at("height"));
			auto boundary = Rect{ x, y, width, height };
			auto object = std::make_unique<GameObject>(boundary);

			objectCollection.boundaries.push_back(std::move(object));
		}
		else if (TRIGGERS.find(name) != TRIGGERS.end()) // rectangle
		{
			auto x = std::stoi(properties.at("x"));
			auto y = std::stoi(properties.at("y"));
			auto width = std::stoi(properties.at("width"));
			auto height = std::stoi(properties.at("height"));
			auto trigger = Rect{ x, y, width, height };
			auto object = std::make_unique<GameObject>(trigger);

			objectCollection.triggers.push_back(std::move(object));
		}
		else if (POSITIONS.find(name) != POSITIONS.end())
		{
			auto x = std::stof(properties.at("x"));
			auto y = std::stof(properties.at("y"));
			auto height = std::stoi(properties.at("height"));
			auto position = Vector2{ x, y - height };

			objectCollection.locations[name] = position;
		}
		else // GameObject (Player, Bat, Skeleton...) // tile
		{
			auto object = ConstructObject(name);
			auto x = std::stof(properties.at("x"));
			auto y = std::stof(properties.at("y"));
			auto height = std::stoi(properties.at("height"));

			object->SetPosition(x, y - height);
			objectCollection.entities.push_back(std::move(object));
		}
	}

	return objectCollection;
}

std::unique_ptr<GameObject> ObjectFactory::ConstructObject(std::string name)
{
	auto type = stringToType.at(name);
	
	switch (type)
	{
		case EntityType::Player:
			return CreatePlayer();

		case EntityType::Bat:
			return std::make_unique<Bat>();

		case EntityType::FirePit:
			return std::make_unique<FirePit>();

		default:
			throw std::invalid_argument("Object name is invalid");
	}
}

std::unique_ptr<Player> ObjectFactory::CreatePlayer()
{
	auto player = std::make_unique<Player>();

	player->SetController(std::make_unique<Controller>(*player.get()));

	return player;
}

std::unique_ptr<Player> ObjectFactory::CreateSimon()
{
	return std::unique_ptr<Player>();
}