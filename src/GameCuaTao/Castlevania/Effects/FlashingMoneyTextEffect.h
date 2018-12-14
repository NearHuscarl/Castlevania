#pragma once

#include "IEffect.h"
#include "Direct2DGame/Extensions/Animations/AnimatedSprite.h"
#include "Direct2DGame/Utilities/Stopwatch.h"

namespace Castlevania
{
	class FlashingMoneyTextEffect : public IEffect
	{
	public:
		FlashingMoneyTextEffect(std::shared_ptr<AnimationFactory> moneyTextAnimation);

		void Show(Vector2 position) override;
		bool IsFinished() override;

		void Update(GameTime gameTime) override;
		void Draw(SpriteExtensions &spriteBatch) override;

	private:
		Vector2 position;
		std::unique_ptr<AnimatedSprite> moneyText;

		Stopwatch lifespanTimer;
	};
}