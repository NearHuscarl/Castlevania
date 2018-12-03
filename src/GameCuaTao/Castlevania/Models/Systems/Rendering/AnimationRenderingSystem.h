#pragma once

#include "Direct2DGame/Extensions/Animations/AnimatedSprite.h"
#include "RenderingSystem.h"

namespace Castlevania
{
	class AnimationRenderingSystem : public RenderingSystem
	{
	public:
		AnimationRenderingSystem(GameObject &parent, std::string spriteConfigPath);

		Sprite &GetSprite() override;
		GameObject &GetParent() override;

		void LoadContent(ContentManager &content) override;
		void Update(GameTime gameTime) override;
		void Draw(SpriteExtensions &spriteBatch) override;

	protected:
		GameObject &parent;
		std::unique_ptr<AnimatedSprite> sprite;
		std::string spriteConfigPath;
	};
}
