#include "SpriteRenderingSystem.h"

using namespace Castlevania;

//SpriteRenderingSystem::SpriteRenderingSystem(SpriteExtensions &spriteBatch, AnimatedSprite &animatedSprite) :
//	spriteBatch{ spriteBatch },
//	animatedSprite{ animatedSprite },
//	sprite{ nullptr }
//{
//}

SpriteRenderingSystem::SpriteRenderingSystem(SpriteExtensions &spriteBatch, Sprite &sprite) :
	spriteBatch { spriteBatch },
	animatedSprite{ animatedSprite },
	sprite{ nullptr }
{
}

void SpriteRenderingSystem::Draw(GameTime gameTime)
{
	spriteBatch.Draw(sprite, transform);
}