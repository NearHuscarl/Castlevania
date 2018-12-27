#pragma once

#include "IEffect.h"
#include "Direct2DGame/Extensions/Sprites/Sprite.h"
#include "Direct2DGame/Utilities/Stopwatch.h"

namespace Castlevania
{
	class DebrisEffect : public IEffect
	{
	public:
		DebrisEffect(std::shared_ptr<Texture> debrisTexture);

		void Show(Vector2 position) override;
		bool IsFinished() override;

		void Update(GameTime gameTime) override;
		void Draw(SpriteExtensions &spriteBatch) override;

	private:
		bool isFinished;

		Vector2 debrisTopLeftVelocity;
		Vector2 debrisTopRightVelocity;
		Vector2 debrisBottomLeftVelocity;
		Vector2 debrisBottomRightVelocity;

		Vector2 debrisTopLeftPosition;
		Vector2 debrisTopRightPosition;
		Vector2 debrisBottomLeftPosition;
		Vector2 debrisBottomRightPosition;

		std::unique_ptr<Sprite> debris;
		Stopwatch lifespanTimer;
	};
}