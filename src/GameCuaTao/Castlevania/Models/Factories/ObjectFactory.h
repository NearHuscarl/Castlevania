#pragma once

#include "../GameObject.h"
#include "../Characters/Player/Player.h"
#include "../Characters/Bat.h"
#include "../Items/FirePit.h"
#include "../Weapons/Whip.h"
#include "../Items/Powerup.h"
#include "../../Effects/EffectFactory.h"

namespace Castlevania
{
	class ObjectFactory
	{
	public:
		ObjectFactory(ContentManager &content);

		std::unique_ptr<Bat> CreateBat(Vector2 position = Vector2::Zero());
		std::unique_ptr<Player> CreatePlayer(Vector2 position = Vector2::Zero());
		std::unique_ptr<Player> CreateSimon(Vector2 position = Vector2::Zero());
		std::unique_ptr<FirePit> CreateFirePit(EntityType itemType, Vector2 position = Vector2::Zero());
		std::unique_ptr<Whip> CreateWhip(GameObject &gameObject);
		std::unique_ptr<Whip> CreateFlashingWhip(GameObject &gameObject);
		std::unique_ptr<RangedWeapon> CreateKnife(Vector2 position = Vector2::Zero());
		
		std::unique_ptr<Powerup> CreatePowerup(EntityType type, Vector2 position = Vector2::Zero());
		std::unique_ptr<Powerup> CreateKnifeItem(Vector2 position = Vector2::Zero());
		std::unique_ptr<Powerup> CreateHeart(Vector2 position = Vector2::Zero());
		std::unique_ptr<Powerup> CreateWhipPowerup(Vector2 position = Vector2::Zero());

	private:
		ContentManager &content;
		std::unique_ptr<EffectFactory> effectManager;
	};
}