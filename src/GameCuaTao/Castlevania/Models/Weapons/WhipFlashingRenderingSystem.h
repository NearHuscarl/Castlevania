#pragma once

#include "../Systems/Rendering/IAnimationRenderingSystem.h"

namespace Castlevania
{
	class Whip;

	class WhipFlashingRenderingSystem : public IAnimationRenderingSystem
	{
	public:
		WhipFlashingRenderingSystem(Whip &parent, std::string spriteConfigPath);

		RectF GetBoundingBox() override;
		AnimatedSprite &GetSprite() override;

		void LoadContent(ContentManager &content) override;
		void Update(float deltaTime) override;
		void Draw(SpriteExtensions &spriteBatch) override;

	private:
		Whip &parent;
		int currentColor;

		std::unique_ptr<AnimatedSprite> spriteMagenta;
		std::unique_ptr<AnimatedSprite> spriteRed;
		std::unique_ptr<AnimatedSprite> spriteYellow;
		std::unique_ptr<AnimatedSprite> spriteBlue;

		std::string spriteConfigPath;

		bool IsEnabledChanged();
		void OnEnabledChange();
	};
}
