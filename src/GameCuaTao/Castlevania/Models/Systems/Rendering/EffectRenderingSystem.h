#pragma once

#include "Direct2DGame/Extensions/Animations/AnimatedSprite.h"
#include "RenderingSystem.h"
#include "../../../Effects/IEffect.h"

namespace Castlevania
{
	// Rendering system for interactive objects that spawns effect when being hit (candle, enemies)
	class EffectRenderingSystem : public RenderingSystem
	{
	public:
		EffectRenderingSystem(std::string spriteConfigPath, std::unique_ptr<IEffect> effect);

		Sprite &GetSprite() override;
		GameObject &GetParent() override;
		void Receive(int message) override;

		void LoadContent(ContentManager &content) override;
		void Update(GameTime gameTime) override;
		void Draw(SpriteExtensions &spriteBatch) override;

	protected:
		std::unique_ptr<AnimatedSprite> sprite;

	private:
		std::string spriteConfigPath;
		std::unique_ptr<IEffect> hitEffect;

		virtual void OnMoveStateChanged();
		virtual void OnStateChanged();
	};
}
