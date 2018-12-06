#pragma once

#include "Direct2DGame/Extensions/Animations/AnimatedSprite.h"
#include "VampireBat.h"
#include "../../Systems/Rendering/EffectRenderingSystem.h"

namespace Castlevania
{
	class VampireBatRenderingSystem : public EffectRenderingSystem
	{
	public:
		VampireBatRenderingSystem(VampireBat &parent, std::string animationPath, std::unique_ptr<IEffect> effect);

		Sprite &GetSprite() override;
		GameObject &GetParent() override;

	private:
		VampireBat &parent;

		void OnMoveStateChanged() override;
	};
}
