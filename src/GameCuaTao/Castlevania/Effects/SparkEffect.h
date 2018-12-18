#pragma once

#include "IEffect.h"
#include "Direct2DGame/Extensions/Sprites/Sprite.h"
#include "Direct2DGame/Utilities/Stopwatch.h"

namespace Castlevania
{
	class SparkEffect : public IEffect
	{
	public:
		SparkEffect(std::shared_ptr<Texture> sparkTexture);

		void Show(Vector2 position) override;
		bool IsFinished() override;

		void Update(GameTime gameTime) override;
		void Draw(SpriteExtensions &spriteBatch) override;

	private:
		bool isFinished;
		Vector2 position;
		std::unique_ptr<Sprite> spark;

		Stopwatch sparkLifespanTimer;
	};
}