#pragma once

#include "../GameObject.h"
#include "../Characters/Player/Player.h"
#include "../Characters/Enemies/Zombie.h"
#include "../Characters/Enemies/Panther.h"
#include "../Items/Brazier.h"
#include "../Weapons/Whip.h"
#include "../Weapons/Dagger.h"
#include "../Items/Powerup.h"
#include "../../Effects/EffectFactory.h"

namespace Castlevania
{
	class ObjectFactory
	{
	public:
		ObjectFactory(ContentManager &content);

		std::unique_ptr<GameObject> CreateBoundary(RectF rect);
		std::unique_ptr<GameObject> CreateRectangleObject(EntityType type, RectF rect);
		std::unique_ptr<Trigger> CreateTrigger(RectF rect, TriggerType triggerType);

		std::unique_ptr<GameObject> CreateBat(Vector2 position = Vector2::Zero());
		std::unique_ptr<Player> CreatePlayer(Vector2 position = Vector2::Zero());
		std::unique_ptr<Player> CreateIntroSimon(Vector2 position = Vector2::Zero());
		std::unique_ptr<Brazier> CreateBrazier(EntityType itemType, Vector2 position = Vector2::Zero());

		std::unique_ptr<Zombie> CreateZombie(Vector2 position = Vector2::Zero());
		std::unique_ptr<Panther> CreatePanther(Vector2 position = Vector2::Zero());

		std::unique_ptr<Whip> CreateWhip(GameObject &gameObject);
		std::unique_ptr<Whip> CreateFlashingWhip(GameObject &gameObject);
		std::unique_ptr<Dagger> CreateDagger(Vector2 position = Vector2::Zero());
		
		std::unique_ptr<Powerup> CreatePowerup(EntityType type, Vector2 position = Vector2::Zero());
		std::unique_ptr<Powerup> CreateDaggerItem(Vector2 position = Vector2::Zero());
		std::unique_ptr<Powerup> CreateLargeHeart(Vector2 position = Vector2::Zero());
		std::unique_ptr<Powerup> CreateWhipPowerup(Vector2 position = Vector2::Zero());

		std::unique_ptr<GameObject> CreateCastle(Vector2 position = Vector2::Zero());
		std::unique_ptr<GameObject> CreateDirtBlock(Vector2 position = Vector2::Zero());

	private:
		ContentManager &content;
		std::unique_ptr<EffectFactory> effectManager;

		void ReadEnemyConfig(Enemy &enemy, std::string configPath);
	};
}