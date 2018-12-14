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
		Vector2 waterLeftVelocity;
		Vector2 waterTopVelocity;
		Vector2 waterRightVelocity;

		Vector2 waterLeftPosition;
		Vector2 waterTopPosition;
		Vector2 waterRightPosition;

		std::unique_ptr<Sprite> water;
		Stopwatch lifespanTimer;
	};
}