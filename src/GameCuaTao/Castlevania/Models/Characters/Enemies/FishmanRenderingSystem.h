#pragma once

#include "Fishman.h"
#include "../../Systems/Rendering/EffectRenderingSystem.h"

namespace Castlevania
{
	class FishmanRenderingSystem : public EffectRenderingSystem
	{
	public:
		FishmanRenderingSystem(Fishman &parent, std::string animationPath, std::unique_ptr<IEffect> effect);
		GameObject &GetParent() override;

	private:
		Fishman &parent;

		void OnMoveStateChanged() override;
	};
}
