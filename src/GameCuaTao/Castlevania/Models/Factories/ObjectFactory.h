#pragma once

#include "../GameObject.h"
#include "../Characters/Player/Player.h"
#include "../Characters/Enemies/Zombie.h"
#include "../Characters/Enemies/Panther.h"
#include "../Characters/Enemies/Fishman.h"
#include "../Characters/Enemies/VampireBat.h"
#include "../Items/Container.h"
#include "../Items/Door.h"
#include "../Items/Fireball.h"
#include "../Weapons/Whip.h"
#include "../Items/MoneyBag.h"
#include "../Items/Powerup.h"
#include "../Spawners/SpawnArea.h"
#include "../Spawners/SpawnPoint.h"
#include "../Areas/WaterArea.h"
#include "../../Effects/EffectFactory.h"

namespace Castlevania
{
	class ObjectFactory
	{
	public:
		ObjectFactory(ContentManager &content);

		std::unique_ptr<GameObject> CreateBoundary(RectF rect);
		std::unique_ptr<GameObject> CreateViewportArea(RectF rect);
		std::unique_ptr<WaterArea> CreateWaterArea(RectF rect);
		std::unique_ptr<SpawnPoint> CreateSpawnPoint(EntityType type, RectF rect);
		std::unique_ptr<SpawnArea> CreateSpawnArea(EntityType type, RectF rect);
		std::unique_ptr<GameObject> CreateRectangleObject(EntityType type, RectF rect);
		std::unique_ptr<Trigger> CreateTrigger(RectF rect, TriggerType triggerType);

		std::unique_ptr<GameObject> CreateBat(Vector2 position = Vector2::Zero());
		std::unique_ptr<Player> CreatePlayer(Vector2 position = Vector2::Zero());
		std::unique_ptr<Player> CreateIntroSimon(Vector2 position = Vector2::Zero());
		std::unique_ptr<Container> CreateBrazier(EntityType itemType, Vector2 position = Vector2::Zero());
		std::unique_ptr<Container> CreateCandle(EntityType itemType, Vector2 position = Vector2::Zero());

		std::unique_ptr<Enemy> CreateEnemy(EntityType type, Vector2 position = Vector2::Zero());
		std::unique_ptr<Zombie> CreateZombie(Vector2 position = Vector2::Zero());
		std::unique_ptr<Panther> CreatePanther(Vector2 position = Vector2::Zero());
		std::unique_ptr<Fishman> CreateFishman(Vector2 position = Vector2::Zero());
		std::unique_ptr<VampireBat> CreateVampireBat(Vector2 position = Vector2::Zero());

		std::unique_ptr<Whip> CreateWhip(GameObject &gameObject);
		std::unique_ptr<Whip> CreateFlashingWhip(GameObject &gameObject);
		std::unique_ptr<RangedWeapon> CreateDagger(Vector2 position = Vector2::Zero());
		std::unique_ptr<Fireball> CreateFireball(Vector2 position = Vector2::Zero());

		std::unique_ptr<Powerup> CreatePowerup(EntityType type, Vector2 position = Vector2::Zero());
		std::unique_ptr<MoneyBag> CreateMoneyBag(EntityType type, Vector2 position = Vector2::Zero());
		std::unique_ptr<MoneyBag> CreateBlueMoneyBag(Vector2 position = Vector2::Zero());
		std::unique_ptr<MoneyBag> CreateWhiteMoneyBag(Vector2 position = Vector2::Zero());
		std::unique_ptr<MoneyBag> CreateRedMoneyBag(Vector2 position = Vector2::Zero());
		std::unique_ptr<MoneyBag> CreateFlashingMoneyBag(Vector2 position = Vector2::Zero());
		std::unique_ptr<Powerup> CreateDaggerItem(Vector2 position = Vector2::Zero());
		std::unique_ptr<Powerup> CreateLargeHeart(Vector2 position = Vector2::Zero());
		std::unique_ptr<Powerup> CreateSmallHeart(Vector2 position = Vector2::Zero());
		std::unique_ptr<Powerup> CreateWhipPowerup(Vector2 position = Vector2::Zero());

		std::unique_ptr<Door> CreateDoor(Vector2 position = Vector2::Zero());
		std::unique_ptr<GameObject> CreateCastle(Vector2 position = Vector2::Zero());
		std::unique_ptr<GameObject> CreateDirtBlock(Vector2 position = Vector2::Zero());

	private:
		ContentManager &content;
		std::unique_ptr<EffectFactory> effectFactory;

		void ReadEnemyConfig(Enemy &enemy, Dictionary stats);
		void ReadSpawnAreaConfig(SpawnArea &spawnArea, Dictionary stats);

		std::unique_ptr<SpawnArea> ConstructSpawnArea(EntityType type);
	};
}