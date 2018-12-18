#pragma once

#include "VampireBat.h"
#include "../../Systems/Rendering/EffectRenderingSystem.h"

namespace Castlevania
{
	class VampireBatRenderingSystem : public EffectRenderingSystem
	{
	public:
		VampireBatRenderingSystem(
			VampireBat &parent,
			std::string animationPath,
			std::unique_ptr<IEffect> deadEffect,
			std::unique_ptr<IEffect> hitEffect);

	private:
		VampireBat &parent;
		void OnMoveStateChanged() override;
	};
}
