#pragma once

#include "EffectRenderingSystem.h"

namespace Castlevania
{
	// Rendering system for interactive objects that spawns effect when being hit (candle, enemies)
	class EntityRenderingSystem : public EffectRenderingSystem
	{
	public:
		EntityRenderingSystem(GameObject &parent, std::string spriteConfigPath, std::unique_ptr<IEffect> effect);

		GameObject &GetParent() override;

	private:
		GameObject &parent;
	};
}
