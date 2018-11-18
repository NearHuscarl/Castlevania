#include "ObjectFactory.h"
#include "../Models/EntityType.h"
#include "../Models/Characters/Player/Controller.h"
#include "../Models/Systems/CollisionSystem.h"
#include "../Models/Systems/PlayerMovementSystem.h"
#include "../Models/Systems/PlayerResponseSystem.h"
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
		auto type = properties.at("type");

		if (type == BOUNDARY) // rectangle
		{
			auto x = std::stof(properties.at("x"));
			auto y = std::stof(properties.at("y"));
			auto width = std::stof(properties.at("width"));
			auto height = std::stof(properties.at("height"));
			auto boundary = RectF{ x, y, width, height };
			auto object = std::make_unique<GameObject>(boundary);

			objectCollection.boundaries.push_back(std::move(object));
		}
		else if (type == TRIGGER) // rectangle
		{
			auto x = std::stof(properties.at("x"));
			auto y = std::stof(properties.at("y"));
			auto width = std::stof(properties.at("width"));
			auto height = std::stof(properties.at("height"));
			auto trigger = RectF{ x, y, width, height };
			auto object = std::make_unique<GameObject>(trigger);

			objectCollection.triggers.push_back(std::move(object));
		}
		else if (type == POSITION)
		{
			auto x = std::stof(properties.at("x"));
			auto y = std::stof(properties.at("y"));
			auto height = std::stoi(properties.at("height"));
			auto position = Vector2{ x, y - height };

			objectCollection.locations[name] = position;
		}
		else if (type == OBJECT) // GameObject (Player, Bat, Skeleton...) // tile
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
			throw std::invalid_argument("Invalid object name");
	}
}

std::unique_ptr<Player> ObjectFactory::CreatePlayer()
{
	auto player = std::make_unique<Player>();

	auto controller = std::make_unique<Controller>(*player.get());
	auto movementSystem = std::make_unique<PlayerMovementSystem>(*player.get());
	auto collisionSystem = std::make_unique<CollisionSystem>(*player.get());
	auto responseSystem = std::make_unique<PlayerResponseSystem>(*player.get());

	player->Attach<IController>(std::move(controller));
	player->Attach<IMovementSystem>(std::move(movementSystem));
	player->Attach<ICollisionSystem>(std::move(collisionSystem));
	player->Attach<ICollisionResponseSystem>(std::move(responseSystem));

	return player;
}

std::unique_ptr<Player> ObjectFactory::CreateSimon()
{
	return std::unique_ptr<Player>();
}