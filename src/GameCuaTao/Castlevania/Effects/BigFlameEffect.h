#pragma once

#include "IEffect.h"
#include "Direct2DGame/Extensions/Animations/AnimatedSprite.h"
#include "Direct2DGame/Utilities/Stopwatch.h"

namespace Castlevania
{
	class BigFlameEffect : public IEffect
	{
	public:
		BigFlameEffect(std::shared_ptr<Texture> sparkTexture, std::shared_ptr<AnimationFactory> flameAnimation);

		void Show(Vector2 position) override;
		bool IsFinished() override;

		void Update(GameTime gameTime) override;
		void Draw(SpriteExtensions &spriteBatch) override;

	private:
		bool isFinished;
		Vector2 position;
		std::unique_ptr<Sprite> spark;
		std::unique_ptr<AnimatedSprite> flame;

		Stopwatch sparkLifespanTimer;
		Stopwatch flameLifespanTimer;
	};
}