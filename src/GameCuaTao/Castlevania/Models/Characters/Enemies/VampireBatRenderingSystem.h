#pragma once

#include "VampireBat.h"
#include "../../Systems/Rendering/EntityRenderingSystem.h"

namespace Castlevania
{
	class VampireBatRenderingSystem : public EntityRenderingSystem
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
