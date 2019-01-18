#pragma once

#include "IEffect.h"
#include "Direct2DGame/Extensions/Sprites/Sprite.h"
#include "Direct2DGame/Utilities/Stopwatch.h"

namespace Castlevania
{
	class WaterEffect : public IEffect
	{
	public:
		WaterEffect(std::shared_ptr<Texture> waterTexture);

		void Show(Vector2 position) override;
		bool IsFinished() override;

		void Update(GameTime gameTime) override;
		void Draw(SpriteExtensions &spriteBatch) override;

	private:
		bool isFinished;

		Vector2 dropletLeftVelocity;
		Vector2 dropletTopVelocity;
		Vector2 dropletRightVelocity;

		Vector2 dropletLeftPosition;
		Vector2 dropletTopPosition;
		Vector2 dropletRightPosition;

		std::unique_ptr<Sprite> water;
		Stopwatch lifespanTimer;
	};
}