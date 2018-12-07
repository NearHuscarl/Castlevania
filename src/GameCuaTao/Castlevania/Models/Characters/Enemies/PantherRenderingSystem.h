#pragma once

#include "Panther.h"
#include "../../Systems/Rendering/EffectRenderingSystem.h"

namespace Castlevania
{
	class PantherRenderingSystem : public EffectRenderingSystem
	{
	public:
		PantherRenderingSystem(Panther &parent, std::string animationPath, std::unique_ptr<IEffect> effect);

		GameObject &GetParent() override;
		void Draw(SpriteExtensions &spriteBatch) override;

	private:
		Panther &parent;

		void OnMoveStateChanged() override;
	};
}
