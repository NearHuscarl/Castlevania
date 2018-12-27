#pragma once

#include "RenderingSystem.h"
#include "../../../Effects/IEffect.h"

namespace Castlevania
{
	// Rendering system for inanimate objects + effect (fireball)
	class ItemRenderingSystem : public RenderingSystem
	{
	public:
		ItemRenderingSystem(
			GameObject &parent,
			std::string spritePath,
			std::unique_ptr<IEffect> deadEffect,
			std::unique_ptr<IEffect> hitEffect);
		
		ItemRenderingSystem(
			GameObject &parent,
			TextureRegion textureRegion,
			std::unique_ptr<IEffect> deadEffect,
			std::unique_ptr<IEffect> hitEffect);

		Sprite &GetSprite() override;
		GameObject &GetParent() override;

		void LoadContent(ContentManager &content) override;
		void Update(GameTime gameTime) override;
		void Draw(SpriteExtensions &spriteBatch) override;

	private:
		GameObject &parent;
		std::unique_ptr<Sprite> sprite;
		std::unique_ptr<IEffect> deadEffect;
		std::unique_ptr<IEffect> hitEffect;
		std::string spritePath;

		void OnStateChanged() override;
		void OnTakingDamage() override;
	};
}
