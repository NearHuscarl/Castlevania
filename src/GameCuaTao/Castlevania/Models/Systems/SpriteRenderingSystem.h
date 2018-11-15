#pragma once

#include "Direct2DGame/IDrawable.h"
#include "Direct2DGame/Extensions/Sprites/SpriteExtensions.h"
#include "Direct2DGame/Extensions/Sprites/Sprite.h"
#include "Direct2DGame/Extensions/Animations/AnimatedSprite.h"

namespace Castlevania
{
	class SpriteRenderingSystem : public IDrawable
	{
	public:
		SpriteRenderingSystem(SpriteExtensions &spriteBatch, Sprite &sprite);
		//SpriteRenderingSystem(SpriteExtensions &spriteBatch, AnimatedSprite &animatedSprite);

		void Draw(GameTime gameTime) override;

	private:
		SpriteExtensions &spriteBatch;
		Sprite &sprite;
		AnimatedSprite &animatedSprite;
	};
}