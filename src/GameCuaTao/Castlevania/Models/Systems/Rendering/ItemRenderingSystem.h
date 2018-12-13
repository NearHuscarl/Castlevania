#pragma once

#include "RenderingSystem.h"
#include "../../../Effects/IEffect.h"

namespace Castlevania
{
	// Rendering system for interactive objects that spawns effect when being hit (candle, enemies)
	class ItemRenderingSystem : public RenderingSystem
	{
	public:
		ItemRenderingSystem(GameObject &parent, std::string spriteConfigPath, std::unique_ptr<IEffect> effect);
		ItemRenderingSystem(GameObject &parent, TextureRegion textureRegion, std::unique_ptr<IEffect> effect);

		Sprite &GetSprite() override;
		GameObject &GetParent() override;

		void LoadContent(ContentManager &content) override;
		void Update(GameTime gameTime) override;
		void Draw(SpriteExtensions &spriteBatch) override;

	private:
		GameObject &parent;
		std::unique_ptr<Sprite> sprite;
		std::unique_ptr<IEffect> hitEffect;
		std::string spritePath;

		void OnStateChanged() override;
	};
}
