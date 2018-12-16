#pragma once

#include "GiantBat.h"
#include "../../Systems/Rendering/EffectRenderingSystem.h"

namespace Castlevania
{
	class GiantBatRenderingSystem : public EffectRenderingSystem
	{
	public:
		GiantBatRenderingSystem(GiantBat &parent, std::string animationPath, std::unique_ptr<IEffect> effect);
		void Draw(SpriteExtensions &spriteBatch) override;

	private:
		GiantBat &parent;
		void OnMoveStateChanged() override;
	};
}
