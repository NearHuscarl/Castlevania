#include "Direct2DGame/Input/Keyboard.h"
#include "ObjectFactory.h"
#include "../../Utilities/CppExtensions.h"
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
#include "../Systems/Rendering/ItemRenderingSystem.h"
#include "../Systems/Rendering/SpriteRenderingSystem.h"
#include "../Systems/Rendering/EffectRenderingSystem.h"
#include "../Areas/WaterAreaRenderingSystem.h"
#include "../Characters/Player/Controller.h"
#include "../Characters/Player/PlayerMovementSystem.h"
#include "../Characters/Player/PlayerResponseSystem.h"
#include "../Characters/Player/PlayerRenderingSystem.h"
#include "../Characters/Enemies/FishmanControlSystem.h"
#include "../Characters/Enemies/FishmanResponseSystem.h"
#include "../Characters/Enemies/FishmanRenderingSystem.h"
#include "../Characters/Enemies/GiantBatControlSystem.h"
#include "../Characters/Enemies/GiantBatMovementSystem.h"
#include "../Characters/Enemies/GiantBatCollisionSystem.h"
#include "../Characters/Enemies/GiantBatResponseSystem.h"
#include "../Characters/Enemies/GiantBatRenderingSystem.h"
#include "../Characters/Enemies/PantherControlSystem.h"
#include "../Characters/Enemies/PantherCollisionSystem.h"
#include "../Characters/Enemies/PantherResponseSystem.h"
#include "../Characters/Enemies/PantherRenderingSystem.h"
#include "../Characters/Enemies/VampireBatRenderingSystem.h"
#include "../Characters/Enemies/ZombieResponseSystem.h"
#include "../Items/PowerupResponseSystem.h"
#include "../Items/DoorRenderingSystem.h"
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

constexpr auto ITEM_FALL_SPEED = 275.0f;

ObjectFactory::ObjectFactory(ContentManager &content) : content{ content }
{
	effectFactory = std::make_unique<EffectFactory>(content);
	RenderingSystem::LoadContent(content);
}

std::unique_ptr<GameObject> ObjectFactory::CreateRectangleObject(ObjectId type, RectF rect)
{
	auto object = std::make_unique<GameObject>(type);
	auto renderingSystem = std::make_unique<BoundingBoxRenderingSystem>(*object, rect);

	object->SetPosition(Vector2{ rect.left, rect.top });
	object->Attach(std::move(renderingSystem));
	object->LoadContent(content);

	return object;
}

std::unique_ptr<GameObject> ObjectFactory::CreateBoundary(RectF rect)
{
	return CreateRectangleObject(ObjectId::Boundary, rect);
}

std::unique_ptr<WaterArea> ObjectFactory::CreateWaterArea(RectF rect)
{
	auto object = std::make_unique<WaterArea>();
	auto renderingSystem = std::make_unique<WaterAreaRenderingSystem>(*object, rect, *effectFactory);

	object->SetPosition(Vector2{ rect.left, rect.top });
	object->Attach(std::move(renderingSystem));
	object->LoadContent(content);

	return object;
}

std::unique_ptr<SpawnPoint> ObjectFactory::CreateSpawnPoint(ObjectId type, RectF rect)
{
	auto object = std::make_unique<SpawnPoint>(type, *this);
	auto renderingSystem = std::make_unique<BoundingBoxRenderingSystem>(*object, rect);

	object->SetPosition(Vector2{ rect.left, rect.top });
	object->Attach(std::move(renderingSystem));
	object->LoadContent(content);

	return object;
}

std::unique_ptr<SpawnArea> ObjectFactory::CreateSpawnArea(ObjectId type, RectF rect)
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
	auto object = std::make_unique<GameObject>(ObjectId::Bat);
	auto stats = content.Load<Dictionary>("GameStats/Characters/Bat.xml");

	object->SetSpeed(std::stof(stats->at("Speed")));

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
	auto collisionSystem = std::make_unique<StandardCollisionSystem>(*object);
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

std::unique_ptr<Container> ObjectFactory::CreateBrazier(ObjectId itemType, Vector2 position)
{
	auto object = std::make_unique<Container>();

	auto renderingSystem = std::make_unique<EffectRenderingSystem>(*object, "Items/Brazier.ani.xml",
		effectFactory->CreateFlameEffect(),
		effectFactory->CreateSparkEffect());

	auto item = CreatePowerup(itemType);

	object->SetPosition(position);
	object->Attach(std::move(renderingSystem));
	object->SetSpawnedItem(std::move(item));
	object->LoadContent(content);
	
	return object;
}

std::unique_ptr<Container> ObjectFactory::CreateCandle(ObjectId itemType, Vector2 position)
{
	auto object = std::make_unique<Container>();
	auto renderingSystem = std::make_unique<EffectRenderingSystem>(*object, "Items/Candle.ani.xml",
		effectFactory->CreateFlameEffect(),
		effectFactory->CreateSparkEffect());

	auto item = CreatePowerup(itemType);

	object->SetPosition(position);
	object->Attach(std::move(renderingSystem));
	object->SetSpawnedItem(std::move(item));
	object->LoadContent(content);

	return object;
}

std::unique_ptr<Enemy> ObjectFactory::CreateEnemy(ObjectId type, Vector2 position)
{
	switch (type)
	{
		case ObjectId::Zombie:
			return CreateZombie();

		case ObjectId::Panther:
			return CreatePanther();

		case ObjectId::Fishman:
			return CreateFishman();

		case ObjectId::VampireBat:
			return CreateVampireBat();

		case ObjectId::GiantBat:
			return CreateGiantBat();

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
	auto renderingSystem = std::make_unique<EffectRenderingSystem>(*object, "Characters/Enemies/Zombie.ani.xml",
		effectFactory->CreateFlameEffect(),
		effectFactory->CreateSparkEffect());

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
		*object, "Characters/Enemies/Panther.ani.xml",
		effectFactory->CreateFlameEffect(),
		effectFactory->CreateSparkEffect());

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
	auto collisionSystem = std::make_unique<StandardCollisionSystem>(*object);
	auto responseSystem = std::make_unique<FishmanResponseSystem>(*object);
	auto renderingSystem = std::make_unique<FishmanRenderingSystem>(
		*object, "Characters/Enemies/Fishman.ani.xml",
		effectFactory->CreateWaterEffect(),
		effectFactory->CreateFlameEffect(),
		effectFactory->CreateSparkEffect());

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
		*object, "Characters/Enemies/VampireBat.ani.xml",
		effectFactory->CreateFlameEffect(),
		effectFactory->CreateSparkEffect());

	object->SetPosition(position);
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);

	return object;
}

std::unique_ptr<GiantBat> ObjectFactory::CreateGiantBat(Vector2 position)
{
	auto object = std::make_unique<GiantBat>();
	auto stats = content.Load<Dictionary>("GameStats/Characters/GiantBat.xml");

	ReadEnemyConfig(*object.get(), *stats);

	auto attackZoneWidth = std::stoi(stats->at("AttackZoneWidth"));
	auto attackZoneHeight = std::stoi(stats->at("AttackZoneHeight"));
	object->SetAttackZone(Rect{ 0, 0, attackZoneWidth, attackZoneHeight });

	auto threatZoneWidth = std::stoi(stats->at("ThreatZoneWidth"));
	auto threatZoneHeight = std::stoi(stats->at("ThreatZoneHeight"));
	object->SetThreatZone(Rect{ 0, 0, threatZoneWidth, threatZoneHeight });

	object->SetDiveSpeed(std::stof(stats->at("DiveSpeed")));

	auto controlSystem = std::make_unique<GiantBatControlSystem>(*object, *this);
	auto movementSystem = std::make_unique<GiantBatMovementSystem>(*object);
	auto collisionSystem = std::make_unique<GiantBatCollisionSystem>(*object);
	auto responseSystem = std::make_unique<GiantBatResponseSystem>(*object);
	auto renderingSystem = std::make_unique<GiantBatRenderingSystem>(
		*object, "Characters/Enemies/GiantBat.ani.xml",
		effectFactory->CreateBigFlameEffect(),
		effectFactory->CreateSparkEffect());

	object->SetPosition(position);
	object->Attach(std::move(controlSystem));
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);
	object->Idle();

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
	auto object = std::make_unique<RangedWeapon>(ObjectId::Dagger);

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
	auto renderingSystem = std::make_unique<ItemRenderingSystem>(
		*object, "Items/Fireball.png", effectFactory->CreateFlameEffect());

	object->SetPosition(position);
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);

	return object;
}

std::unique_ptr<Powerup> ObjectFactory::CreatePowerup(ObjectId type, Vector2 position)
{
	switch (type)
	{
		case ObjectId::BlueMoneyBag:
			return CreateBlueMoneyBag(position);

		case ObjectId::WhiteMoneyBag:
			return CreateWhiteMoneyBag(position);

		case ObjectId::RedMoneyBag:
			return CreateRedMoneyBag(position);

		case ObjectId::FlashingMoneyBag:
			return CreateFlashingMoneyBag(position);

		case ObjectId::LargeHeart:
			return CreateLargeHeart(position);

		case ObjectId::SmallHeart:
			return CreateSmallHeart(position);

		case ObjectId::WhipPowerup:
			return CreateWhipPowerup(position);

		case ObjectId::DaggerItem:
			return CreateDaggerItem(position);

		default:
			throw std::invalid_argument("Invalid powerup type");
	}
}

std::unique_ptr<MoneyBag> ObjectFactory::CreateMoneyBag(ObjectId type, Vector2 position)
{
	auto money = int{};
	auto spriteId = std::string{};

	switch (type)
	{
		case ObjectId::RedMoneyBag:
			money = 100;
			spriteId = "money_bag_red";
			break;

		case ObjectId::BlueMoneyBag:
			money = 400;
			spriteId = "money_bag_blue";
			break;

		case ObjectId::WhiteMoneyBag:
			money = 700;
			spriteId = "money_bag_white";
			break;
	}

	auto object = std::make_unique<MoneyBag>(money, type);

	auto movementSystem = std::make_unique<SimpleMovementSystem>(*object);
	auto collisionSystem = std::make_unique<StaticCollisionSystem>(*object);
	auto responseSystem = std::make_unique<PowerupResponseSystem>(*object);

	auto moneyAtlas = content.Load<Spritesheet>("Items/Money_Bag.atlas.xml");
	auto effect = effectFactory->CreateMoneyTextEffect(money);
	auto renderingSystem = std::make_unique<ItemRenderingSystem>(
		*object, moneyAtlas->at(spriteId), std::move(effect));

	object->SetPosition(position);
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);
	object->SetVelocity_Y(ITEM_FALL_SPEED); // Fall down

	return object;
}

std::unique_ptr<MoneyBag> ObjectFactory::CreateBlueMoneyBag(Vector2 position)
{
	return CreateMoneyBag(ObjectId::BlueMoneyBag, position);
}

std::unique_ptr<MoneyBag> ObjectFactory::CreateWhiteMoneyBag(Vector2 position)
{
	return CreateMoneyBag(ObjectId::WhiteMoneyBag, position);
}

std::unique_ptr<MoneyBag> ObjectFactory::CreateRedMoneyBag(Vector2 position)
{
	return CreateMoneyBag(ObjectId::RedMoneyBag, position);
}

std::unique_ptr<MoneyBag> ObjectFactory::CreateFlashingMoneyBag(Vector2 position)
{
	auto object = std::make_unique<MoneyBag>(1000, ObjectId::FlashingMoneyBag);

	auto movementSystem = std::make_unique<SimpleMovementSystem>(*object);
	auto collisionSystem = std::make_unique<StaticCollisionSystem>(*object);
	auto responseSystem = std::make_unique<PowerupResponseSystem>(*object);

	auto moneyAtlas = content.Load<Spritesheet>("Items/Money_Bag.atlas.xml");
	auto renderingSystem = std::make_unique<EffectRenderingSystem>(*object, "Items/Money_Bag.ani.xml",
		effectFactory->CreateFlashingMoneyTextEffect(), nullptr);

	object->SetPosition(position);
	object->Attach(std::move(movementSystem));
	object->Attach(std::move(collisionSystem));
	object->Attach(std::move(responseSystem));
	object->Attach(std::move(renderingSystem));

	object->LoadContent(content);
	object->SetVelocity_Y(ITEM_FALL_SPEED); // Fall down

	return object;
}

std::unique_ptr<Powerup> ObjectFactory::CreateDaggerItem(Vector2 position)
{
	auto object = std::make_unique<Powerup>(ObjectId::DaggerItem);

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
	auto object = std::make_unique<Powerup>(ObjectId::LargeHeart);

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
	auto object = std::make_unique<Powerup>(ObjectId::SmallHeart);

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
	object->SetSpeed(120.0f); // Fall down

	return object;
}

std::unique_ptr<Powerup> ObjectFactory::CreateWhipPowerup(Vector2 position)
{
	auto object = std::make_unique<Powerup>(ObjectId::WhipPowerup);

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

std::unique_ptr<GameObject> ObjectFactory::CreateCrystalBall(Vector2 position)
{
	auto object = std::make_unique<GameObject>(ObjectId::CrystalBall);

	auto movementSystem = std::make_unique<SimpleMovementSystem>(*object);
	auto collisionSystem = std::make_unique<StaticCollisionSystem>(*object);
	auto responseSystem = std::make_unique<PowerupResponseSystem>(*object);
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*object, "Items/Crystal_Ball.ani.xml");

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
	auto object = std::make_unique<GameObject>(ObjectId::Castle);
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*object, "TiledMaps/Stage_01/Castle.png");

	object->SetPosition(position);
	object->Attach(std::move(renderingSystem));
	object->LoadContent(content);

	return object;
}

std::unique_ptr<GameObject> ObjectFactory::CreateDirtBlock(Vector2 position)
{
	auto object = std::make_unique<GameObject>(ObjectId::DirtBlock);
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*object, "TiledMaps/Stage_01/Dirt_Block.png");

	object->SetPosition(position);
	object->Attach(std::move(renderingSystem));
	object->LoadContent(content);

	return object;
}

std::unique_ptr<GameObject> ObjectFactory::CreateWaterZone(Vector2 position)
{
	auto object = std::make_unique<GameObject>(ObjectId::Unknown);
	auto renderingSystem = std::make_unique<SpriteRenderingSystem>(*object, "TiledMaps/Stage_01/Water_Area.png");

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
	auto groupSpawnTime = std::stoi(stats.at("GroupSpawnTime"));
	auto spawnTime = std::stoi(stats.at("SpawnTime"));
	auto spawnGroup = stats.at("SpawnGroup");
	auto spawnDirection = stats.at("SpawnDirection");

	spawnArea.SetGroupCountChances(spawnGroup);
	spawnArea.SetDirectionChances(spawnDirection);
	spawnArea.SetGroupSpawnTime(groupSpawnTime);
	spawnArea.SetSpawnTime(spawnTime);
}

std::unique_ptr<SpawnArea> ObjectFactory::ConstructSpawnArea(ObjectId type)
{
	auto object = std::unique_ptr<SpawnArea>{};
	auto stats = std::shared_ptr<Dictionary>{};

	switch (type)
	{
		case ObjectId::Zombie:
		{
			object = std::make_unique<ZombieSpawnArea>(*this);
			stats = content.Load<Dictionary>("GameStats/SpawnAreas/ZombieSpawnArea.xml");
			break;
		}

		case ObjectId::VampireBat:
		{
			object = std::make_unique<VampireBatSpawnArea>(*this);
			stats = content.Load<Dictionary>("GameStats/SpawnAreas/BatSpawnArea.xml");
			break;
		}

		case ObjectId::Fishman:
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
