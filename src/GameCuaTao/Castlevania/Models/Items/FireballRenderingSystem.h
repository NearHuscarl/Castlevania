#pragma once

#include "../Systems/Rendering/RenderingSystem.h"
#include "../../Effects/IEffect.h"

namespace Castlevania
{
	// Rendering system for interactive objects that spawns effect when being hit (candle, enemies)
	class FireballRenderingSystem : public RenderingSystem
	{
	public:
		FireballRenderingSystem(GameObject &parent, std::string spriteConfigPath, std::unique_ptr<IEffect> effect);

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
