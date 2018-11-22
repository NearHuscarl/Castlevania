#pragma once

#include "IEffect.h"
#include "Direct2DGame/Extensions/Animations/AnimatedSprite.h"
#include "Direct2DGame/Utilities/Stopwatch.h"

namespace Castlevania
{
	class FlameEffect : public IEffect
	{
	public:
		FlameEffect(std::shared_ptr<Texture> sparkTexture, std::shared_ptr<AnimationFactory> flameAnimation);

		void Show(Vector2 position) override;
		bool IsFinished() override;
		void Draw(SpriteExtensions &spriteBatch) override;

	private:
		Vector2 position;
		std::unique_ptr<Sprite> spark;
		std::unique_ptr<AnimatedSprite> flames;

		Stopwatch sparkLifespanTimer;
	};
}