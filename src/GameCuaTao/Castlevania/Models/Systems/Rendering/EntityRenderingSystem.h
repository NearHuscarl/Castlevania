#pragma once

#include "AnimationRenderingSystem.h"
#include "../../../Effects/IEffect.h"

namespace Castlevania
{
	// Rendering system for interactive objects that spawns effect when being hit (candle, enemies)
	class EntityRenderingSystem : public AnimationRenderingSystem
	{
	public:
		EntityRenderingSystem(GameObject &parent, std::string spriteConfigPath, std::unique_ptr<IEffect> effect);

		void Receive(int message) override;

		void Update(GameTime gameTime) override;
		void Draw(SpriteExtensions &spriteBatch) override;

	private:
		std::unique_ptr<IEffect> hitEffect;
	};
}
