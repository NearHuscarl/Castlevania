#pragma once

#include "IEffect.h"
#include "Direct2DGame/Extensions/Animations/AnimatedSprite.h"

namespace Castlevania
{
	class FlameEffect : public IEffect
	{
	public:
		FlameEffect(std::shared_ptr<AnimationFactory> flameAnimation);

		void Show(Vector2 position) override;
		bool IsFinished() override;
		
		void Update(GameTime gameTime) override;
		void Draw(SpriteExtensions &spriteBatch) override;

	private:
		bool isFinished;
		Vector2 position;
		std::unique_ptr<AnimatedSprite> flame;
	};
}