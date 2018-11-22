#pragma once

#include "Powerup.h"
#include "../../Effects/IEffect.h"

namespace Castlevania
{
	class FirePit : public GameObject
	{
	public:
		FirePit();

		void SetSpawnedItem(std::unique_ptr<Powerup> item);
		void SetHitEffect(std::unique_ptr<IEffect> effect);

		void Update(float deltaTime, ObjectCollection *objectCollection) override;
		void Draw(SpriteExtensions &spriteBatch) override;

		void OnBeingHit();
		// Spawn item and disappear after hit by player
		std::unique_ptr<GameObject> SpawnItem();

	private:
		enum class FirePitState
		{
			Normal,
			Spawning,
		};

		std::unique_ptr<Powerup> item;
		std::unique_ptr<IEffect> hitEffect;
		
		FirePitState state;
		bool isHit;
	};
}