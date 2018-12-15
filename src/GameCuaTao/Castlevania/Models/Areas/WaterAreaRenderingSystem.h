#pragma once

#include "../Systems/Rendering/RenderingSystem.h"
#include "WaterArea.h"
#include "../../Effects/EffectFactory.h"

namespace Castlevania
{
	// Rendering system for interactive objects that spawns effect when being hit (candle, enemies)
	class WaterAreaRenderingSystem : public RenderingSystem
	{
	public:
		WaterAreaRenderingSystem(WaterArea &parent, RectF boundingBox, EffectFactory &effectFactory);

		Sprite &GetSprite() override;
		GameObject &GetParent() override;

		void Receive(int message) override;

		void LoadContent(ContentManager &content) override;
		void Update(GameTime gameTime) override;
		void Draw(SpriteExtensions &spriteBatch) override;

	private:
		WaterArea &parent;
		std::unique_ptr<Sprite> sprite;
		RectF boundingBox;
		EffectFactory &effectFactory;

		std::vector<std::shared_ptr<IEffect>> effects;
	};
}
