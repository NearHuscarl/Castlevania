#include "Direct2DGame/Input/Keyboard.h"
#include "ObjectFactory.h"
#include "../EntityType.h"
#include "../Systems/Movement/SimpleMovementSystem.h"
#include "../Systems/Collision/CollisionSystem.h"
#include "../Systems/Collision/EntityCollisionSystem.h"
#include "../Systems/Collision/StaticCollisionSystem.h"
#include "../Systems/Collision/StandardCollisionSystem.h"
#include "../Systems/CollisionResponse/StaticResponseSystem.h"
#include "../Systems/Rendering/SpriteRenderingSystem.h"
#include "../Systems/Rendering/AnimationRenderingSystem.h"
#include "../Characters/Player/Controller.h"
#include "../Characters/Player/PlayerMovementSystem.h"
#include "../Characters/Player/PlayerCollisionSystem.h"
#include "../Characters/Player/PlayerResponseSystem.h"
#include "../Characters/Player/PlayerRenderingSystem.h"
#include "../Characters/Enemies/ZombieMovementSystem.h"
#include "../Weapons/WhipRenderingSystem.h"
#include "../Weapons/WhipFlashingRenderingSystem.h"
#include "../Weapons/WhipResponseSystem.h"
#include "../Weapons/DaggerResponseSystem.h"

using namespace Castlevania;

constexpr auto ITEM_FALL_SPEED = 120.0f;

ObjectFactory::ObjectFactory(ContentManager &content) : content{ content }
{
	effectManager = std::make_unique<EffectFactory>(content);
}

std::unique_ptr<GameObject> ObjectFactory::CreateBat(Vector2 position)
{
	auto object = std::make_unique<GameObject>(EntityType::Bat);
	auto stats = content.Load<Dictionary>("CharacterStats/Bat.xml");

	object->SetLinearVelocity(std::stof(stats->at("Speed")));

	auto renderingSystem = std::make_unique<AnimationRenderingSystem>(*object, "Characters/NPCs/Bat.ani.xml");

	object->SetPosition(position);
	object->Attach<IRenderingSystem>(std::move(renderingSystem));
	object->LoadContent(content);

	return object;
}

std::unique_ptr<Player> ObjectFactory::CreatePlayer(Vector2 position)
{
	auto object = std::make_unique<Player>();
	auto stats = content.Load<Dictionary>("CharacterStats/Simon.xml");
	
	object->SetSpeed(std::stof(stats->at("Speed")));
	object->SetJumpSpeed(std::stof(stats->at("JumpSpeed")));

	auto controller = std::make_unique<Controller>(*object, *this);
	auto movementSystem = std::make_unique<PlayerMovementSystem>(*object);
	auto collisionSystem = std::make_unique<PlayerCollisionSystem>(*object);
	auto responseSystem = std::make_unique<PlayerResponseSystem>(*object, *this);
	auto renderingSystem = std::make_unique<PlayerRenderingSystem>(*object, "Characters/Players/Simon.ani.xml");

	Keyboard::Register(controller.get());

	object->SetPosition(position);
	object->Attach<IControlSystem>(std::move(controller));
	object->Attach<IMovementSystem>(std::move(movementSystem));
	object->Attach<ICollisionSystem>(std::move(collisionSystem));
	object->Attach<ICollisionResponseSystem>(std::move(responseSystem));
	object->Attach<IRenderingSystem>(std::move(renderingSystem));

	auto whip = CreateWhip(*object);
	
	object->SetWhip(std::move(whip));
	object->LoadContent(content);

	return object;
}

std::unique_ptr<Player> ObjectFactory::CreateIntroSimon(Vector2 position)
{
	auto object = std::make_unique<Player>();
	auto stats = content.Load<Dictionary>("CharacterStats/Simon.xml");

	object->SetSpeed(std::stof(stats->at("Speed")));

	auto controller = std::make_unique<Controller>(*object, *this); // TODO: make intro controller
	auto movementSystem = std::make_unique<PlayerMovementSystem>(*object);
	auto renderingSystem = std::make_unique<PlayerRenderingSystem>(*object, "Characters/Players/Simon.ani.xml");

	object->SetPosition(position);
	object->Attach<IControlSystem>(std::move(controller));
	object->Attach<IMovementSystem>(std::move(movementSystem));
	object->Attach<IRenderingSystem>(std::move(renderingSystem));

	object->LoadContent(content);

	return object;
}

std::unique_ptr<Brazier> ObjectFactory::CreateBrazier(EntityType itemType, Vector2 position)
{
	auto object = std::make_unique<Brazier>();

	auto renderingSystem = std::make_unique<AnimationRenderingSystem>(*object, "Items/Fire_Pit.ani.xml");
	auto item = CreatePowerup(itemType);
	auto effect = effectManager->CreateFlameEffect();

	object->SetPosition(position);
	object->Attach<IRenderingSystem>(std::move(renderingSystem));
	object->SetSpawnedItem(std::move(item));
	object->SetHitEffect(std::move(effect));
	object->LoadContent(content);
	
	return object;
}

std::unique_ptr<Zombie> ObjectFactory::CreateZombie(Vector2 position)
{
	auto object = std::make_unique<Zombie>();

	ReadEnemyConfig(*object.get(), "CharacterStats/Zombie.xml");

	auto movementSystem = std::make_unique<ZombieMovementSystem>(*object);
	auto renderingSystem = std::make_unique<AnimationRenderingSystem>(*object, "Characters/Enemies/Zombie.ani.xml");

	object->SetPosition(position);
	object->Attach<IMovementSystem>(std::move(movementSystem));
	object->Attach<IRenderingSystem>(std::move(renderingSystem));

	object->LoadContent(content);

	return object;
}

std::unique_ptr<Whip> ObjectFactory::CreateWhip(GameObject &gameObject)
{
	auto object = std::make_unique<Whip>(gameObject);

	auto collisionSystem = std::make_unique<EntityCollisionSystem>(*object);
	auto responseSystem = std::make_unique<WhipResponseSystem>(*object);
	auto renderingSystem = std::make_unique<WhipRenderingSystem>(*object, "Items/Whip.ani.xml");

	object->Attach<ICollisionSystem>(std::move(collisionSystem));
	object->Attach<ICollisionResponseSystem>(std::move(responseSystem));
	object->Attach<IRenderingSystem>(std::move(renderingSystem));

	object->LoadContent(content);

	return object;
}

std::unique_ptr<Whip> ObjectFactory::CreateFlashingWhip(GameObject &gameObject)
{
	auto object = std::make_unique<Whip>(gameObject);

	auto collisionSystem = std::make_unique<EntityCollisionSystem>(*object);
	auto responseSystem = std::make_unique<WhipResponseSystem>(*object);
	auto renderingSystem = std::make_unique<WhipFlashingRenderingSystem>(*object, "Items/Whip.ani.xml");

	object->Attach<ICollisionSystem>(std::move(collisionSystem));
	object->Attach<ICollisionResponseSystem>(std::move(responseSystem));
	object->Attach<IRenderingSystem>(std::move(renderingSystem));

	object->LoadContent(content);

	return object;
}

std::unique_ptr<Dagger> ObjectFactory::CreateDagger(Vector2 position)
{
	auto object = std::make_unique<Dagger>();

	auto movementSystem = std::make_unique<SimpleMovementSystem>(*object);
	auto collisionSystem = std::make_unique<EntityCollisionSystem>(*object);
	auto responseSystem = std::make_unique<DaggerResponseSystem>(*object);
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*object, "Items/Dagger.png");

	object->SetPosition(position);
	object->Attach<IMovementSystem>(std::move(movementSystem));
	object->Attach<ICollisionSystem>(std::move(collisionSystem));
	object->Attach<ICollisionResponseSystem>(std::move(responseSystem));
	object->Attach<IRenderingSystem>(std::move(renderingSystem));

	object->LoadContent(content);

	return object;
}

std::unique_ptr<Powerup> ObjectFactory::CreatePowerup(EntityType type, Vector2 position)
{
	switch (type)
	{
		case EntityType::LargeHeart:
			return CreateLargeHeart(position);

		case EntityType::WhipPowerup:
			return CreateWhipPowerup(position);

		case EntityType::DaggerItem:
			return CreateDaggerItem(position);

		default:
			throw std::invalid_argument("Invalid powerup type");
	}
}

std::unique_ptr<Powerup> ObjectFactory::CreateDaggerItem(Vector2 position)
{
	auto object = std::make_unique<Powerup>(EntityType::DaggerItem);

	auto movementSystem = std::make_unique<SimpleMovementSystem>(*object);
	auto collisionSystem = std::make_unique<StaticCollisionSystem>(*object);
	auto responseSystem = std::make_unique<StaticResponseSystem>(*object);
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*object, "Items/Dagger.png");

	object->SetPosition(position);
	object->Attach<IMovementSystem>(std::move(movementSystem));
	object->Attach<ICollisionSystem>(std::move(collisionSystem));
	object->Attach<ICollisionResponseSystem>(std::move(responseSystem));
	object->Attach<IRenderingSystem>(std::move(renderingSystem));

	object->LoadContent(content);
	object->SetVelocity_Y(ITEM_FALL_SPEED); // Fall down

	return object;
}

std::unique_ptr<Powerup> ObjectFactory::CreateLargeHeart(Vector2 position)
{
	auto object = std::make_unique<Powerup>(EntityType::LargeHeart);

	auto movementSystem = std::make_unique<SimpleMovementSystem>(*object);
	auto collisionSystem = std::make_unique<StaticCollisionSystem>(*object);
	auto responseSystem = std::make_unique<StaticResponseSystem>(*object);
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*object, "Items/Large_Heart.png");
	
	object->SetPosition(position);
	object->Attach<IMovementSystem>(std::move(movementSystem));
	object->Attach<ICollisionSystem>(std::move(collisionSystem));
	object->Attach<ICollisionResponseSystem>(std::move(responseSystem));
	object->Attach<IRenderingSystem>(std::move(renderingSystem));
	
	object->LoadContent(content);
	object->SetVelocity_Y(ITEM_FALL_SPEED); // Fall down

	return object;
}

std::unique_ptr<Powerup> ObjectFactory::CreateWhipPowerup(Vector2 position)
{
	auto object = std::make_unique<Powerup>(EntityType::WhipPowerup);

	auto movementSystem = std::make_unique<SimpleMovementSystem>(*object);
	auto collisionSystem = std::make_unique<StaticCollisionSystem>(*object);
	auto responseSystem = std::make_unique<StaticResponseSystem>(*object);
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*object, "Items/Whip_Powerup.png");

	object->SetPosition(position);
	object->Attach<IMovementSystem>(std::move(movementSystem));
	object->Attach<ICollisionSystem>(std::move(collisionSystem));
	object->Attach<ICollisionResponseSystem>(std::move(responseSystem));
	object->Attach<IRenderingSystem>(std::move(renderingSystem));
	
	object->LoadContent(content);
	object->SetVelocity_Y(ITEM_FALL_SPEED); // Fall down

	return object;
}

std::unique_ptr<GameObject> ObjectFactory::CreateCastle(Vector2 position)
{
	auto object = std::make_unique<GameObject>(EntityType::Castle);
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*object, "TiledMaps/Stage_01/Castle.png");

	object->SetPosition(position);
	object->Attach<IRenderingSystem>(std::move(renderingSystem));
	object->LoadContent(content);

	return object;
}

std::unique_ptr<GameObject> ObjectFactory::CreateDirtBlock(Vector2 position)
{
	auto object = std::make_unique<GameObject>(EntityType::DirtBlock);
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*object, "Textures/Dirt_Block.png");

	object->SetPosition(position);
	object->Attach<IRenderingSystem>(std::move(renderingSystem));
	object->LoadContent(content);

	return object;
}

void ObjectFactory::ReadEnemyConfig(Enemy &enemy, std::string configPath)
{
	auto stats = content.Load<Dictionary>(configPath);

	enemy.SetSpeed(std::stof(stats->at("Speed")));
	enemy.SetHealth(std::stoi(stats->at("Health")));
	enemy.SetAttack(std::stoi(stats->at("Attack")));
	enemy.SetExp(std::stoi(stats->at("Exp")));
}
