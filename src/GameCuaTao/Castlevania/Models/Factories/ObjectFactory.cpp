#include "Direct2DGame/Input/Keyboard.h"
#include "ObjectFactory.h"
#include "../../Utilities/TypeConverter.h"
#include "../Systems/Movement/SimpleMovementSystem.h"
#include "../Systems/Movement/EntityMovementSystem.h"
#include "../Systems/Movement/WaveMovementSystem.h"
#include "../Systems/Collision/CollisionSystem.h"
#include "../Systems/Collision/EntityCollisionSystem.h"
#include "../Systems/Collision/SimpleCollisionSystem.h"
#include "../Systems/Collision/StaticCollisionSystem.h"
#include "../Systems/Collision/StandardCollisionSystem.h"
#include "../Systems/CollisionResponse/GroundResponseSystem.h"
#include "../Systems/Rendering/AnimationRenderingSystem.h"
#include "../Systems/Rendering/BoundingboxRenderingSystem.h"
#include "../Systems/Rendering/SpriteRenderingSystem.h"
#include "../Systems/Rendering/EffectRenderingSystem.h"
#include "../Characters/Player/Controller.h"
#include "../Characters/Player/PlayerMovementSystem.h"
#include "../Characters/Player/PlayerCollisionSystem.h"
#include "../Characters/Player/PlayerResponseSystem.h"
#include "../Characters/Player/PlayerRenderingSystem.h"
#include "../Characters/Enemies/FishmanControlSystem.h"
#include "../Characters/Enemies/FishmanResponseSystem.h"
#include "../Characters/Enemies/FishmanRenderingSystem.h"
#include "../Characters/Enemies/PantherControlSystem.h"
#include "../Characters/Enemies/PantherCollisionSystem.h"
#include "../Characters/Enemies/PantherResponseSystem.h"
#include "../Characters/Enemies/PantherRenderingSystem.h"
#include "../Characters/Enemies/VampireBatRenderingSystem.h"
#include "../Characters/Enemies/ZombieResponseSystem.h"
#include "../Items/PowerupResponseSystem.h"
#include "../Items/DoorRenderingSystem.h"
#include "../Items/FireballRenderingSystem.h"
#include "../Spawners/SpawnerCollisionSystem.h"
#include "../Spawners/SpawnAreaResponseSystem.h"
#include "../Weapons/WhipCollisionSystem.h"
#include "../Weapons/WhipRenderingSystem.h"
#include "../Weapons/WhipFlashingRenderingSystem.h"
#include "../Weapons/WhipResponseSystem.h"
#include "../Weapons/DaggerResponseSystem.h"
#include "../Spawners/ZombieSpawnArea.h"
#include "../Spawners/VampireBatSpawnArea.h"
#include "../Spawners/FishmanSpawnArea.h"

using namespace Castlevania;

constexpr auto ITEM_FALL_SPEED = 120.0f;

ObjectFactory::ObjectFactory(ContentManager &content) : content{ content }
{
	effectManager = std::make_unique<EffectFactory>(content);
}

std::unique_ptr<GameObject> ObjectFactory::CreateBoundary(RectF rect)
{
	return CreateRectangleObject(EntityType::Boundary, rect);
}

std::unique_ptr<GameObject> ObjectFactory::CreateViewportArea(RectF rect)
{
	return CreateRectangleObject(EntityType::ViewportArea, rect);
}

std::unique_ptr<SpawnPoint> ObjectFactory::CreateSpawnPoint(EntityType type, RectF rect)
{
	auto object = std::make_unique<SpawnPoint>(type, *this);
	auto renderingSystem = std::make_unique<BoundingBoxRenderingSystem>(*object, rect);

	object->SetPosition(Vector2{ rect.left, rect.top });
	object->Attach(std::move(renderingSystem));
	object->LoadContent(content);

	return object;
}

std::unique_ptr<SpawnArea> ObjectFactory::CreateSpawnArea(EntityType type, RectF rect)
{
	auto object = ConstructSpawnArea(type);
	auto collisionSystem = std::make_unique<SpawnerCollisionSystem>(*object);
	auto responseSystem = std::make_unique<SpawnAreaResponseSystem>(*object);
	auto renderingSystem = std::make_unique<BoundingBoxRenderingSystem>(*object, rect);

	object->SetPosition(Vector2{ rect.left, rect.top });
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));
	object->LoadContent(content);

	return object;
}

std::unique_ptr<GameObject> ObjectFactory::CreateRectangleObject(EntityType type, RectF rect)
{
	auto object = std::make_unique<GameObject>(type);
	auto renderingSystem = std::make_unique<BoundingBoxRenderingSystem>(*object, rect);

	object->SetPosition(Vector2{ rect.left, rect.top });
	object->Attach(std::move(renderingSystem));
	object->LoadContent(content);

	return object;
}

std::unique_ptr<Trigger> ObjectFactory::CreateTrigger(RectF rect, TriggerType triggerType)
{
	auto object = std::make_unique<Trigger>(triggerType);
	auto renderingSystem = std::make_unique<BoundingBoxRenderingSystem>(*object, rect);

	object->SetPosition(Vector2{ rect.left, rect.top });
	object->Attach(std::move(renderingSystem));
	object->LoadContent(content);

	return object;
}

std::unique_ptr<GameObject> ObjectFactory::CreateBat(Vector2 position)
{
	auto object = std::make_unique<GameObject>(EntityType::Bat);
	auto stats = content.Load<Dictionary>("GameStats/Characters/Bat.xml");

	object->SetLinearVelocity(std::stof(stats->at("Speed")));

	//auto renderingSystem = std::make_unique<AnimationRenderingSystem>(*object, "Characters/NPCs/Bat.ani.xml");
	auto renderingSystem = std::make_unique<BoundingBoxRenderingSystem>(*object, RectF::Empty());

	object->SetPosition(position);
	object->Attach(std::move(renderingSystem));
	object->LoadContent(content);

	return object;
}

std::unique_ptr<Player> ObjectFactory::CreatePlayer(Vector2 position)
{
	auto object = std::make_unique<Player>();
	auto stats = content.Load<Dictionary>("GameStats/Characters/Simon.xml");
	
	object->SetSpeed(std::stof(stats->at("Speed")));
	object->SetJumpSpeed(std::stof(stats->at("JumpSpeed")));

	auto controller = std::make_unique<Controller>(*object, *this);
	auto movementSystem = std::make_unique<PlayerMovementSystem>(*object);
	auto collisionSystem = std::make_unique<PlayerCollisionSystem>(*object);
	auto responseSystem = std::make_unique<PlayerResponseSystem>(*object, *this);
	auto renderingSystem = std::make_unique<PlayerRenderingSystem>(*object, "Characters/Players/Simon.ani.xml");

	Keyboard::Register(controller.get());

	object->SetPosition(position);
	object->Attach(std::move(controller));
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	auto whip = CreateWhip(*object);
	
	object->SetWhip(std::move(whip));
	object->LoadContent(content);

	return object;
}

std::unique_ptr<Player> ObjectFactory::CreateIntroSimon(Vector2 position)
{
	auto object = std::make_unique<Player>();
	auto stats = content.Load<Dictionary>("GameStats/Characters/Simon.xml");

	object->SetSpeed(std::stof(stats->at("Speed")));

	auto controller = std::make_unique<Controller>(*object, *this); // TODO: make intro controller
	auto movementSystem = std::make_unique<PlayerMovementSystem>(*object);
	auto renderingSystem = std::make_unique<PlayerRenderingSystem>(*object, "Characters/Players/Simon.ani.xml");

	object->SetPosition(position);
	object->Attach(std::move(controller));
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);

	return object;
}

std::unique_ptr<Container> ObjectFactory::CreateBrazier(EntityType itemType, Vector2 position)
{
	auto object = std::make_unique<Container>();

	auto renderingSystem = std::make_unique<EffectRenderingSystem>(
		*object, "Items/Brazier.ani.xml", effectManager->CreateFlameEffect());
	auto item = CreatePowerup(itemType);

	object->SetPosition(position);
	object->Attach(std::move(renderingSystem));
	object->SetSpawnedItem(std::move(item));
	object->LoadContent(content);
	
	return object;
}

std::unique_ptr<Container> ObjectFactory::CreateCandle(EntityType itemType, Vector2 position)
{
	auto object = std::make_unique<Container>();

	auto renderingSystem = std::make_unique<EffectRenderingSystem>(
		*object, "Items/Candle.ani.xml", effectManager->CreateFlameEffect());
	auto item = CreatePowerup(itemType);

	object->SetPosition(position);
	object->Attach(std::move(renderingSystem));
	object->SetSpawnedItem(std::move(item));
	object->LoadContent(content);

	return object;
}

std::unique_ptr<Enemy> ObjectFactory::CreateEnemy(EntityType type, Vector2 position)
{
	switch (type)
	{
		case EntityType::Zombie:
			return CreateZombie();

		case EntityType::Panther:
			return CreatePanther();

		case EntityType::VampireBat:
			return CreateVampireBat();

		case EntityType::Fishman:
			return CreateFishman();

		default:
			throw std::runtime_error("Object type not supported");
	}
}

std::unique_ptr<Zombie> ObjectFactory::CreateZombie(Vector2 position)
{
	auto object = std::make_unique<Zombie>();
	auto stats = content.Load<Dictionary>("GameStats/Characters/Zombie.xml");

	ReadEnemyConfig(*object.get(), *stats);

	auto movementSystem = std::make_unique<EntityMovementSystem>(*object, 1000.0f);
	auto collisionSystem = std::make_unique<StaticCollisionSystem>(*object);
	auto responseSystem = std::make_unique<ZombieResponseSystem>(*object);
	auto renderingSystem = std::make_unique<EffectRenderingSystem>(
		*object, "Characters/Enemies/Zombie.ani.xml", effectManager->CreateFlameEffect());

	object->SetPosition(position);
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);

	return object;
}

std::unique_ptr<Panther> ObjectFactory::CreatePanther(Vector2 position)
{
	auto object = std::make_unique<Panther>();
	auto stats = content.Load<Dictionary>("GameStats/Characters/Panther.xml");

	ReadEnemyConfig(*object.get(), *stats);

	auto zoneWidth = std::stoi(stats->at("ActiveZoneWidth"));
	auto zoneHeight = std::stoi(stats->at("ActiveZoneHeight"));
	object->SetActiveZone(Rect{ 0, 0, zoneWidth, zoneHeight });
	object->SetJumpSpeed(std::stof(stats->at("JumpSpeed")));

	auto controlSystem = std::make_unique<PantherControlSystem>(*object);
	auto movementSystem = std::make_unique<EntityMovementSystem>(*object, 1000.0f);
	auto collisionSystem = std::make_unique<PantherCollisionSystem>(*object);
	auto responseSystem = std::make_unique<PantherResponseSystem>(*object);
	auto renderingSystem = std::make_unique<PantherRenderingSystem>(
		*object, "Characters/Enemies/Panther.ani.xml", effectManager->CreateFlameEffect());

	object->SetPosition(position);
	object->Attach(std::move(controlSystem));
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);

	return object;
}

std::unique_ptr<Fishman> ObjectFactory::CreateFishman(Vector2 position)
{
	auto object = std::make_unique<Fishman>();
	auto stats = content.Load<Dictionary>("GameStats/Characters/Fishman.xml");

	ReadEnemyConfig(*object.get(), *stats);
	object->SetLaunchSpeed(std::stof(stats->at("LaunchSpeed")));

	auto controlSystem = std::make_unique<FishmanControlSystem>(*object, *this);
	auto movementSystem = std::make_unique<EntityMovementSystem>(*object, 1000.0f);
	auto collisionSystem = std::make_unique<StaticCollisionSystem>(*object);
	auto responseSystem = std::make_unique<FishmanResponseSystem>(*object);
	auto renderingSystem = std::make_unique<FishmanRenderingSystem>(
		*object, "Characters/Enemies/Fishman.ani.xml", effectManager->CreateFlameEffect());

	object->SetPosition(position);
	object->Attach(std::move(controlSystem));
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);

	return object;
}

std::unique_ptr<VampireBat> ObjectFactory::CreateVampireBat(Vector2 position)
{
	auto object = std::make_unique<VampireBat>();
	auto stats = content.Load<Dictionary>("GameStats/Characters/VampireBat.xml");

	ReadEnemyConfig(*object.get(), *stats);

	auto movementSystem = std::make_unique<WaveMovementSystem>(*object, 0.2f, 1.0f, Axis::X);
	auto renderingSystem = std::make_unique<VampireBatRenderingSystem>(
		*object, "Characters/Enemies/VampireBat.ani.xml", effectManager->CreateFlameEffect());

	object->SetPosition(position);
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);

	return object;
}

std::unique_ptr<Whip> ObjectFactory::CreateWhip(GameObject &gameObject)
{
	auto object = std::make_unique<Whip>(gameObject);

	auto collisionSystem = std::make_unique<WhipCollisionSystem>(*object);
	auto responseSystem = std::make_unique<WhipResponseSystem>(*object);
	auto renderingSystem = std::make_unique<WhipRenderingSystem>(*object, "Items/Whip.ani.xml");

	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);

	return object;
}

std::unique_ptr<Whip> ObjectFactory::CreateFlashingWhip(GameObject &gameObject)
{
	auto object = std::make_unique<Whip>(gameObject);

	auto collisionSystem = std::make_unique<WhipCollisionSystem>(*object);
	auto responseSystem = std::make_unique<WhipResponseSystem>(*object);
	auto renderingSystem = std::make_unique<WhipFlashingRenderingSystem>(*object, "Items/Whip.ani.xml");

	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);

	return object;
}

std::unique_ptr<RangedWeapon> ObjectFactory::CreateDagger(Vector2 position)
{
	auto object = std::make_unique<RangedWeapon>(EntityType::Dagger);

	auto movementSystem = std::make_unique<SimpleMovementSystem>(*object);
	auto collisionSystem = std::make_unique<EntityCollisionSystem>(*object);
	auto responseSystem = std::make_unique<DaggerResponseSystem>(*object);
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*object, "Items/Dagger.png");

	object->SetPosition(position);
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);

	return object;
}

std::unique_ptr<Fireball> ObjectFactory::CreateFireball(Vector2 position)
{
	auto object = std::make_unique<Fireball>();
	auto stats = content.Load<Dictionary>("GameStats/Items/Fireball.xml");

	object->SetSpeed(std::stof(stats->at("Speed")));
	object->SetAttack(std::stoi(stats->at("Attack")));

	auto movementSystem = std::make_unique<SimpleMovementSystem>(*object);
	auto renderingSystem = std::make_unique<FireballRenderingSystem>(
		*object, "Items/Fireball.png", effectManager->CreateFlameEffect());

	object->SetPosition(position);
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);

	return object;
}

std::unique_ptr<Powerup> ObjectFactory::CreatePowerup(EntityType type, Vector2 position)
{
	switch (type)
	{
		case EntityType::LargeHeart:
			return CreateLargeHeart(position);

		case EntityType::SmallHeart:
			return CreateSmallHeart(position);

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
	auto responseSystem = std::make_unique<PowerupResponseSystem>(*object);
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*object, "Items/Dagger.png");

	object->SetPosition(position);
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);
	object->SetVelocity_Y(ITEM_FALL_SPEED); // Fall down

	return object;
}

std::unique_ptr<Powerup> ObjectFactory::CreateLargeHeart(Vector2 position)
{
	auto object = std::make_unique<Powerup>(EntityType::LargeHeart);

	auto movementSystem = std::make_unique<SimpleMovementSystem>(*object);
	auto collisionSystem = std::make_unique<StaticCollisionSystem>(*object);
	auto responseSystem = std::make_unique<PowerupResponseSystem>(*object);
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*object, "Items/Large_Heart.png");
	
	object->SetPosition(position);
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));
	
	object->LoadContent(content);
	object->SetVelocity_Y(ITEM_FALL_SPEED); // Fall down

	return object;
}

std::unique_ptr<Powerup> ObjectFactory::CreateSmallHeart(Vector2 position)
{
	auto object = std::make_unique<Powerup>(EntityType::SmallHeart);

	auto movementSystem = std::make_unique<WaveMovementSystem>(*object, 0.5f, 1.8f, Axis::Y);
	auto collisionSystem = std::make_unique<StaticCollisionSystem>(*object);
	auto responseSystem = std::make_unique<PowerupResponseSystem>(*object);
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*object, "Items/Small_Heart.png");

	object->SetPosition(position);
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);
	object->SetSpeed(ITEM_FALL_SPEED); // Fall down

	return object;
}

std::unique_ptr<Powerup> ObjectFactory::CreateWhipPowerup(Vector2 position)
{
	auto object = std::make_unique<Powerup>(EntityType::WhipPowerup);

	auto movementSystem = std::make_unique<SimpleMovementSystem>(*object);
	auto collisionSystem = std::make_unique<StaticCollisionSystem>(*object);
	auto responseSystem = std::make_unique<PowerupResponseSystem>(*object);
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*object, "Items/Whip_Powerup.png");

	object->SetPosition(position);
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));
	
	object->LoadContent(content);
	object->SetVelocity_Y(ITEM_FALL_SPEED); // Fall down

	return object;
}

std::unique_ptr<Door> ObjectFactory::CreateDoor(Vector2 position)
{
	auto object = std::make_unique<Door>();
	auto renderingSystem = std::make_unique<DoorRenderingSystem>(*object, "Items/Door.ani.xml");

	object->SetPosition(position);
	object->Attach(std::move(renderingSystem));
	object->LoadContent(content);
	object->Idle();

	return object;
}

std::unique_ptr<GameObject> ObjectFactory::CreateCastle(Vector2 position)
{
	auto object = std::make_unique<GameObject>(EntityType::Castle);
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*object, "TiledMaps/Stage_01/Castle.png");

	object->SetPosition(position);
	object->Attach(std::move(renderingSystem));
	object->LoadContent(content);

	return object;
}

std::unique_ptr<GameObject> ObjectFactory::CreateDirtBlock(Vector2 position)
{
	auto object = std::make_unique<GameObject>(EntityType::DirtBlock);
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*object, "TiledMaps/Stage_01/Dirt_Block.png");

	object->SetPosition(position);
	object->Attach(std::move(renderingSystem));
	object->LoadContent(content);

	return object;
}

void ObjectFactory::ReadEnemyConfig(Enemy &enemy, Dictionary stats)
{
	enemy.SetSpeed(std::stof(stats.at("Speed")));
	enemy.SetHealth(std::stoi(stats.at("Health")));
	enemy.SetAttack(std::stoi(stats.at("Attack")));
	enemy.SetExp(std::stoi(stats.at("Exp")));
}

void ObjectFactory::ReadSpawnAreaConfig(SpawnArea &spawnArea, Dictionary stats)
{
	auto spawnType = string2EntityType.at(stats.at("Spawn"));
	auto spawnGroup = std::stoi(stats.at("SpawnGroup"));
	auto groupSpawnTime = std::stoi(stats.at("GroupSpawnTime"));
	auto spawnTime = std::stoi(stats.at("SpawnTime"));

	spawnArea.SetSpawnGroupCount(spawnGroup);
	spawnArea.SetGroupSpawnTime(groupSpawnTime);
	spawnArea.SetSpawnTime(spawnTime);
}

std::unique_ptr<SpawnArea> ObjectFactory::ConstructSpawnArea(EntityType type)
{
	auto object = std::unique_ptr<SpawnArea>{};
	auto stats = std::shared_ptr<Dictionary>{};

	switch (type)
	{
		case EntityType::Zombie:
		{
			object = std::make_unique<ZombieSpawnArea>(*this);
			stats = content.Load<Dictionary>("GameStats/SpawnAreas/ZombieSpawnArea.xml");
			break;
		}

		case EntityType::VampireBat:
		{
			object = std::make_unique<VampireBatSpawnArea>(*this);
			stats = content.Load<Dictionary>("GameStats/SpawnAreas/BatSpawnArea.xml");
			break;
		}

		case EntityType::Fishman:
		{
			object = std::make_unique<FishmanSpawnArea>(*this);
			stats = content.Load<Dictionary>("GameStats/SpawnAreas/FishmanSpawnArea.xml");
			break;
			return object;
		}

		default:
			throw std::runtime_error("Spawn area for this type of object is not supported");
	}

	ReadSpawnAreaConfig(*object.get(), *stats);

	return object;
}
