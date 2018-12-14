#pragma once

#include "../Systems/Rendering/RenderingSystem.h"
#include "../../Effects/WaterEffect.h"
#include "WaterArea.h"

namespace Castlevania
{
	// Rendering system for interactive objects that spawns effect when being hit (candle, enemies)
	class WaterAreaRenderingSystem : public RenderingSystem
	{
	public:
		WaterAreaRenderingSystem(WaterArea &parent);

		Sprite &GetSprite() override;
		GameObject &GetParent() override;

		void LoadContent(ContentManager &content) override;
		void Update(GameTime gameTime) override;
		void Draw(SpriteExtensions &spriteBatch) override;

	private:
		WaterArea &parent;
		std::unique_ptr<Sprite> sprite;
		std::vector<WaterEffect> effects;
	};
}
