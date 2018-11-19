#pragma once

#include "Direct2DGame/Extensions/Animations/AnimatedSprite.h"
#include "IAnimationRenderingSystem.h"

namespace Castlevania
{
	class AnimationRenderingSystem : public IAnimationRenderingSystem
	{
	public:
		AnimationRenderingSystem(AnimatedObject &parent, std::string spriteConfigPath);

		RectF GetBoundingBox() override;
		AnimatedSprite &GetSprite() override;

		void LoadContent(ContentManager &content) override;
		void Update(float deltaTime) override;
		void Draw(SpriteExtensions &spriteBatch) override;

	protected:
		AnimatedObject &parent;
		std::unique_ptr<AnimatedSprite> sprite;
		std::string spriteConfigPath;
	};
}
