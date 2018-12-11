#pragma once

#include "Direct2DGame/Extensions/Animations/AnimatedSprite.h"
#include "RenderingSystem.h"

namespace Castlevania
{
	class AnimationRenderingSystem : public RenderingSystem
	{
	public:
		AnimationRenderingSystem(std::string spriteConfigPath);

		Sprite &GetSprite() override;
		GameObject &GetParent() override = 0;

		void LoadContent(ContentManager &content) override;
		void Update(GameTime gameTime) override;
		void Draw(SpriteExtensions &spriteBatch) override;

	protected:
		std::unique_ptr<AnimatedSprite> sprite;
		std::string spriteConfigPath;
	};
}
