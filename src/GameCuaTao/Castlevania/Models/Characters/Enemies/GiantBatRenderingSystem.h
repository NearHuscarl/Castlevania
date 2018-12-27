#pragma once

#include "GiantBat.h"
#include "../../Systems/Rendering/EntityRenderingSystem.h"

namespace Castlevania
{
	class GiantBatRenderingSystem : public EntityRenderingSystem
	{
	public:
		GiantBatRenderingSystem(
			GiantBat &parent,
			std::string animationPath,
			std::unique_ptr<IEffect> deadEffect,
			std::unique_ptr<IEffect> hitEffect);

		void Draw(SpriteExtensions &spriteBatch) override;

	private:
		GiantBat &parent;
		void OnMoveStateChanged() override;
	};
}
