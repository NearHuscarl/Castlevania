#include "ObjectFactory.h"
#include "../Models/EntityType.h"
#include "../Models/RectangleObject.h"
#include "../Models/Characters/Player/Controller.h"
#include "../Models/Characters/Player/PlayerMovementSystem.h"
#include "../Models/Characters/Player/PlayerResponseSystem.h"
#include "../Models/Systems/CollisionSystem.h"
#include "../Models/Systems/SimpleCollisionSystem.h"
#include "../Models/Systems/AnimationRenderingSystem.h"
#include "../Models/Characters/Bat.h"
#include "../Models/Items/FirePit.h"
#include "../Models/Weapons/WhipResponseSystem.h"

using namespace Castlevania;

ObjectFactory::ObjectFactory()
{
	stringToType =
	{
		{ "Player", EntityType::Player },
		{ "Bat", EntityType::Bat },
		{ "Cloud", EntityType::Cloud },
		{ "FirePit", EntityType::FirePit },
		{ "Whip", EntityType::Whip },
		{ "Knife", EntityType::Knife },
		{ "Heart", EntityType::Heart },
		{ "WhipPowerup", EntityType::WhipPowerup },
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
			auto object = std::make_unique<RectangleObject>(boundary);

			objectCollection.boundaries.push_back(std::move(object));
		}
		else if (type == TRIGGER) // rectangle
		{
			auto x = std::stof(properties.at("x"));
			auto y = std::stof(properties.at("y"));
			auto width = std::stof(properties.at("width"));
			auto height = std::stof(properties.at("height"));
			auto trigger = RectF{ x, y, width, height };
			auto object = std::make_unique<RectangleObject>(trigger);

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
			auto object = ConstructObject(properties);
			auto x = std::stof(properties.at("x"));
			auto y = std::stof(properties.at("y"));
			auto height = std::stoi(properties.at("height"));

			object->SetPosition(x, y - height);
			objectCollection.entities.push_back(std::move(object));
		}
	}

	return objectCollection;
}

std::unique_ptr<GameObject> ObjectFactory::ConstructObject(ObjectProperties properties)
{
	auto name = properties.at("name");
	auto type = stringToType.at(name);
	
	switch (type)
	{
		case EntityType::Player:
			return CreatePlayer();

		case EntityType::Bat:
			return std::make_unique<Bat>();

		case EntityType::FirePit:
			return CreateFirePit(properties);

		case EntityType::Knife:
			return std::make_unique<Knife>();

		case EntityType::Heart:
			return std::make_unique<Heart>();

		case EntityType::WhipPowerup:
			return std::make_unique<WhipPowerup>();

		default:
			throw std::invalid_argument("Invalid object name");
	}
}

std::unique_ptr<Bat> ObjectFactory::CreateBat()
{
	auto bat = std::unique_ptr<Bat>();
	auto renderingSystem = std::make_unique<AnimationRenderingSystem>(*bat, "Characters/NPCs/Bat.xml");

	bat->AttachRenderer<IAnimationRenderingSystem>(std::move(renderingSystem));

	return bat;
}

std::unique_ptr<Player> ObjectFactory::CreatePlayer()
{
	auto player = std::make_unique<Player>();

	auto controller = std::make_unique<Controller>(*player);
	auto movementSystem = std::make_unique<PlayerMovementSystem>(*player);
	auto collisionSystem = std::make_unique<CollisionSystem>(*player);
	auto responseSystem = std::make_unique<PlayerResponseSystem>(*player);
	auto renderingSystem = std::make_unique<AnimationRenderingSystem>(*player, "Characters/Players/Simon.xml");

	player->Attach<IController>(std::move(controller));
	player->Attach<IMovementSystem>(std::move(movementSystem));
	player->Attach<ICollisionSystem>(std::move(collisionSystem));
	player->Attach<ICollisionResponseSystem>(std::move(responseSystem));
	player->AttachRenderer<IAnimationRenderingSystem>(std::move(renderingSystem));

	auto whip = CreateWhip(*player);
	
	player->SetWhip(std::move(whip));

	return player;
}

std::unique_ptr<Player> ObjectFactory::CreateSimon()
{
	return std::unique_ptr<Player>();
}

std::unique_ptr<FirePit> ObjectFactory::CreateFirePit(ObjectProperties properties)
{
	auto firePit = std::make_unique<FirePit>();
	auto renderingSystem = std::make_unique<AnimationRenderingSystem>(*firePit, "Items/Fire_Pit.xml");
	auto item = ConstructObject({ {"name", properties.at("Item")} });

	firePit->AttachRenderer<IAnimationRenderingSystem>(std::move(renderingSystem));
	firePit->SetSpawnedItem(std::move(item));
	
	return firePit;
}

std::unique_ptr<Whip> ObjectFactory::CreateWhip(GameObject &gameObject)
{
	auto whip = std::make_unique<Whip>(gameObject);

	auto collisionSystem = std::make_unique<SimpleCollisionSystem>(*whip);
	auto responseSystem = std::make_unique<WhipResponseSystem>(*whip);
	auto renderingSystem = std::make_unique<AnimationRenderingSystem>(*whip, "Items/Whip.xml");

	whip->Attach<ICollisionSystem>(std::move(collisionSystem));
	whip->Attach<ICollisionResponseSystem>(std::move(responseSystem));
	whip->AttachRenderer<IAnimationRenderingSystem>(std::move(renderingSystem));

	return whip;
}
