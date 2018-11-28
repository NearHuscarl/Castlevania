#pragma once

#include "Powerup.h"
#include "../../Effects/IEffect.h"

namespace Castlevania
{
	class Brazier : public GameObject
	{
	public:
		Brazier();

		void SetSpawnedItem(std::unique_ptr<Powerup> item);
		void SetHitEffect(std::unique_ptr<IEffect> effect);

		void Update(GameTime gameTime, UpdateData &updateData) override;
		void Draw(SpriteExtensions &spriteBatch) override;

		void OnBeingHit();
		// Spawn item and disappear after hit by player
		std::unique_ptr<GameObject> SpawnItem();

	private:
		enum class BrazierState
		{
			Normal,
			Spawning,
		};

		std::unique_ptr<Powerup> item;
		std::unique_ptr<IEffect> hitEffect;
		
		BrazierState state;
		bool isHit;
	};
}