#pragma once

#include "Direct2DGame/Extensions/Animations/AnimatedSprite.h"
#include "IRenderingSystem.h"

namespace Castlevania
{
	class AnimationRenderingSystem : public IRenderingSystem
	{
	public:
		AnimationRenderingSystem(GameObject &parent, std::string spriteConfigPath);

		RectF GetBoundingBox() override;
		Sprite &GetSprite() override;

		virtual void Receive(int message) override {};

		void LoadContent(ContentManager &content) override;
		void Update(float deltaTime) override;
		void Draw(SpriteExtensions &spriteBatch) override;

	protected:
		GameObject &parent;
		std::unique_ptr<AnimatedSprite> sprite;
		std::string spriteConfigPath;
	};
}
