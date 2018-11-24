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

		std::unique_ptr<Bat> CreateBat();
		std::unique_ptr<Player> CreatePlayer();
		std::unique_ptr<Player> CreateSimon();
		std::unique_ptr<FirePit> CreateFirePit(EntityType itemType);
		std::unique_ptr<Whip> CreateWhip(GameObject &gameObject);
		std::unique_ptr<Whip> CreateFlashingWhip(GameObject &gameObject);
		std::unique_ptr<RangedWeapon> CreateKnife();
		
		std::unique_ptr<Powerup> CreatePowerup(EntityType type);
		std::unique_ptr<Powerup> CreateKnifeItem();
		std::unique_ptr<Powerup> CreateHeart();
		std::unique_ptr<Powerup> CreateWhipPowerup();

	private:
		ContentManager &content;
		std::unique_ptr<EffectFactory> effectManager;
	};
}