#pragma once

#include "WhipRenderingSystem.h"

namespace Castlevania
{
	class Whip;

	class WhipFlashingRenderingSystem : public WhipRenderingSystem
	{
	public:
		WhipFlashingRenderingSystem(Whip &parent, std::string spriteConfigPath);

		void LoadContent(ContentManager &content) override;
		void Update(float deltaTime) override;
		void Draw(SpriteExtensions &spriteBatch) override;

	private:
		int currentColor;

		std::unique_ptr<AnimatedSprite> spriteRed;
		std::unique_ptr<AnimatedSprite> spriteYellow;
		std::unique_ptr<AnimatedSprite> spriteBlue;

		void OnEnabledChanged() override;
	};
}
