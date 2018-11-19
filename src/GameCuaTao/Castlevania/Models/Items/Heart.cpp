#include "Heart.h"

using namespace Castlevania;

Heart::Heart() : StaticObject(EntityType::Heart)
{
}

void Heart::LoadContent(ContentManager &content)
{
	//auto animationFactory = content.Load<AnimationFactory>("Items/Heart.xml");
	//animations = std::make_unique<AnimatedSprite>(animationFactory);
}

void Heart::Draw(SpriteExtensions &spriteBatch)
{
}
