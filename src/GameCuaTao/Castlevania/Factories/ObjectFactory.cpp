#include "ObjectFactory.h"
#include "../Models/EntityType.h"
#include "../Models/RectangleObject.h"
#include "../Models/Systems/Movement/MovementSystem.h"
#include "../Models/Systems/Collision/CollisionSystem.h"
#include "../Models/Systems/Collision/EntityCollisionSystem.h"
#include "../Models/Systems/Collision/StaticCollisionSystem.h"
#include "../Models/Systems/Collision/StandardCollisionSystem.h"
#include "../Models/Systems/CollisionResponse/StaticResponseSystem.h"
#include "../Models/Systems/Rendering/SpriteRenderingSystem.h"
#include "../Models/Systems/Rendering/AnimationRenderingSystem.h"
#include "../Models/Characters/Player/Controller.h"
#include "../Models/Characters/Player/PlayerMovementSystem.h"
#include "../Models/Characters/Player/PlayerCollisionSystem.h"
#include "../Models/Characters/Player/PlayerResponseSystem.h"
#include "../Models/Characters/Player/PlayerRenderingSystem.h"
#include "../Models/Weapons/WhipRenderingSystem.h"
#include "../Models/Weapons/WhipFlashingRenderingSystem.h"
#include "../Models/Weapons/WhipResponseSystem.h"
#include "../Models/Weapons/KnifeResponseSystem.h"

using namespace Castlevania;

constexpr auto ITEM_FALL_SPEED = 120.0f;

ObjectFactory::ObjectFactory(ContentManager &content) : content{ content }
{
	stringToType =
	{
		{ "Player", EntityType::Player },
		{ "Bat", EntityType::Bat },
		{ "Cloud", EntityType::Cloud },
		{ "FirePit", EntityType::FirePit },
		{ "Whip", EntityType::Whip },
		{ "KnifeItem", EntityType::KnifeItem },
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
			return CreateBat();

		case EntityType::FirePit:
			return CreateFirePit(properties);

		case EntityType::Knife:
			return CreateKnife();

		case EntityType::Heart:
			return CreateHeart();

		case EntityType::WhipPowerup:
			return CreateWhipPowerup();

		case EntityType::KnifeItem:
			return CreateKnifeItem();

		default:
			throw std::invalid_argument("Invalid object name");
	}
}

std::unique_ptr<Bat> ObjectFactory::CreateBat()
{
	auto bat = std::unique_ptr<Bat>();
	auto renderingSystem = std::make_unique<AnimationRenderingSystem>(*bat, "Characters/NPCs/Bat.ani.xml");

	bat->Attach<IRenderingSystem>(std::move(renderingSystem));
	bat->LoadContent(content);

	return bat;
}

std::unique_ptr<Player> ObjectFactory::CreatePlayer()
{
	auto player = std::make_unique<Player>();

	auto controller = std::make_unique<Controller>(*player, *this);
	auto movementSystem = std::make_unique<PlayerMovementSystem>(*player);
	auto collisionSystem = std::make_unique<PlayerCollisionSystem>(*player);
	auto responseSystem = std::make_unique<PlayerResponseSystem>(*player, *this);
	auto renderingSystem = std::make_unique<PlayerRenderingSystem>(*player, "Characters/Players/Simon.ani.xml");

	player->Attach<IController>(std::move(controller));
	player->Attach<IMovementSystem>(std::move(movementSystem));
	player->Attach<ICollisionSystem>(std::move(collisionSystem));
	player->Attach<ICollisionResponseSystem>(std::move(responseSystem));
	player->Attach<IRenderingSystem>(std::move(renderingSystem));

	auto whip = CreateWhip(*player);
	
	player->SetWhip(std::move(whip));
	player->LoadContent(content);

	return player;
}

std::unique_ptr<Player> ObjectFactory::CreateSimon()
{
	return std::unique_ptr<Player>();
}

std::unique_ptr<FirePit> ObjectFactory::CreateFirePit(ObjectProperties properties)
{
	auto firePit = std::make_unique<FirePit>();

	auto renderingSystem = std::make_unique<AnimationRenderingSystem>(*firePit, "Items/Fire_Pit.ani.xml");
	auto item = ConstructObject({ {"name", properties.at("Item")} });

	firePit->Attach<IRenderingSystem>(std::move(renderingSystem));
	firePit->SetSpawnedItem(std::move(item));
	firePit->LoadContent(content);
	
	return firePit;
}

std::unique_ptr<Whip> ObjectFactory::CreateWhip(GameObject &gameObject)
{
	auto whip = std::make_unique<Whip>(gameObject);

	auto collisionSystem = std::make_unique<EntityCollisionSystem>(*whip);
	auto responseSystem = std::make_unique<WhipResponseSystem>(*whip);
	auto renderingSystem = std::make_unique<WhipRenderingSystem>(*whip, "Items/Whip.ani.xml");

	whip->Attach<ICollisionSystem>(std::move(collisionSystem));
	whip->Attach<ICollisionResponseSystem>(std::move(responseSystem));
	whip->Attach<IRenderingSystem>(std::move(renderingSystem));

	whip->LoadContent(content);

	return whip;
}

std::unique_ptr<Whip> ObjectFactory::CreateFlashingWhip(GameObject &gameObject)
{
	auto whip = std::make_unique<Whip>(gameObject);

	auto collisionSystem = std::make_unique<EntityCollisionSystem>(*whip);
	auto responseSystem = std::make_unique<WhipResponseSystem>(*whip);
	auto renderingSystem = std::make_unique<WhipFlashingRenderingSystem>(*whip, "Items/Whip.ani.xml");

	whip->Attach<ICollisionSystem>(std::move(collisionSystem));
	whip->Attach<ICollisionResponseSystem>(std::move(responseSystem));
	whip->Attach<IRenderingSystem>(std::move(renderingSystem));

	whip->LoadContent(content);

	return whip;
}

std::unique_ptr<RangedWeapon> ObjectFactory::CreateKnife()
{
	auto knife = std::make_unique<RangedWeapon>(EntityType::Knife);

	auto movementSystem = std::make_unique<MovementSystem>(*knife);
	auto collisionSystem = std::make_unique<EntityCollisionSystem>(*knife);
	auto responseSystem = std::make_unique<KnifeResponseSystem>(*knife);
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*knife, "Items/Knife.png");

	knife->Attach<IMovementSystem>(std::move(movementSystem));
	knife->Attach<ICollisionSystem>(std::move(collisionSystem));
	knife->Attach<ICollisionResponseSystem>(std::move(responseSystem));
	knife->Attach<IRenderingSystem>(std::move(renderingSystem));

	knife->LoadContent(content);

	return knife;
}

std::unique_ptr<GameObject> ObjectFactory::CreateKnifeItem()
{
	auto knifeItem = std::make_unique<GameObject>(EntityType::KnifeItem);

	auto movementSystem = std::make_unique<MovementSystem>(*knifeItem);
	auto collisionSystem = std::make_unique<StaticCollisionSystem>(*knifeItem);
	auto responseSystem = std::make_unique<StaticResponseSystem>(*knifeItem);
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*knifeItem, "Items/Knife.png");

	knifeItem->Attach<IMovementSystem>(std::move(movementSystem));
	knifeItem->Attach<ICollisionSystem>(std::move(collisionSystem));
	knifeItem->Attach<ICollisionResponseSystem>(std::move(responseSystem));
	knifeItem->Attach<IRenderingSystem>(std::move(renderingSystem));

	knifeItem->LoadContent(content);
	knifeItem->SetVelocity_Y(ITEM_FALL_SPEED); // Fall down

	return knifeItem;
}

std::unique_ptr<GameObject> ObjectFactory::CreateHeart()
{
	auto heart = std::make_unique<GameObject>(EntityType::Heart);

	auto movementSystem = std::make_unique<MovementSystem>(*heart);
	auto collisionSystem = std::make_unique<StaticCollisionSystem>(*heart);
	auto responseSystem = std::make_unique<StaticResponseSystem>(*heart);
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*heart, "Items/Heart.png");
	
	heart->Attach<IMovementSystem>(std::move(movementSystem));
	heart->Attach<ICollisionSystem>(std::move(collisionSystem));
	heart->Attach<ICollisionResponseSystem>(std::move(responseSystem));
	heart->Attach<IRenderingSystem>(std::move(renderingSystem));
	
	heart->LoadContent(content);
	heart->SetVelocity_Y(ITEM_FALL_SPEED); // Fall down

	return heart;
}

std::unique_ptr<GameObject> ObjectFactory::CreateWhipPowerup()
{
	auto whipPowerup = std::make_unique<GameObject>(EntityType::WhipPowerup);

	auto movementSystem = std::make_unique<MovementSystem>(*whipPowerup);
	auto collisionSystem = std::make_unique<StaticCollisionSystem>(*whipPowerup);
	auto responseSystem = std::make_unique<StaticResponseSystem>(*whipPowerup);
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*whipPowerup, "Items/Whip_Powerup.png");

	whipPowerup->Attach<IMovementSystem>(std::move(movementSystem));
	whipPowerup->Attach<ICollisionSystem>(std::move(collisionSystem));
	whipPowerup->Attach<ICollisionResponseSystem>(std::move(responseSystem));
	whipPowerup->Attach<IRenderingSystem>(std::move(renderingSystem));
	
	whipPowerup->LoadContent(content);
	whipPowerup->SetVelocity_Y(ITEM_FALL_SPEED); // Fall down

	return whipPowerup;
}
