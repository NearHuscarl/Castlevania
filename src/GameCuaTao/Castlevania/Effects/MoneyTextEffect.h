#pragma once

#include "IEffect.h"
#include "Direct2DGame/Extensions/Sprites/Sprite.h"
#include "Direct2DGame/Utilities/Stopwatch.h"

namespace Castlevania
{
	class MoneyTextEffect : public IEffect
	{
	public:
		MoneyTextEffect(std::shared_ptr<Texture> moneyTextTexture);

		void Show(Vector2 position) override;
		bool IsFinished() override;

		void Update(GameTime gameTime) override;
		void Draw(SpriteExtensions &spriteBatch) override;

	private:
		bool isFinished;
		Vector2 position;
		std::unique_ptr<Sprite> moneyText;

		Stopwatch lifespanTimer;
	};
}