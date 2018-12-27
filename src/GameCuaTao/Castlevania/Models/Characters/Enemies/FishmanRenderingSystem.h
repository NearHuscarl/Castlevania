#pragma once

#include "Fishman.h"
#include "../../Systems/Rendering/EntityRenderingSystem.h"

namespace Castlevania
{
	class FishmanRenderingSystem : public EntityRenderingSystem
	{
	public:
		FishmanRenderingSystem(
			Fishman &parent,
			std::string animationPath,
			std::unique_ptr<IEffect> launchEffect,
			std::unique_ptr<IEffect> deadEffect,
			std::unique_ptr<IEffect> hitEffect);

		void Update(GameTime gameTime) override;
		void Draw(SpriteExtensions &spriteBatch) override;

	private:
		Fishman &parent;
		std::unique_ptr<IEffect> launchEffect;

		void OnMoveStateChanged() override;
	};
}
