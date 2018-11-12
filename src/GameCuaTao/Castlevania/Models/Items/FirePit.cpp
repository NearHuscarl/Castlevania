#include "FirePit.h"

using namespace Castlevania;

FirePit::FirePit() : GameObject(EntityType::FirePit)
{
}

void FirePit::LoadContent(ContentManager &content)
{
	auto animationFactory = content.Load<AnimationFactory>("Items/Fire_Pit.xml");
	sprite = std::make_unique<AnimatedSprite>(animationFactory);
}

void FirePit::Update(float deltaTime)
{
}

void FirePit::Draw(SpriteExtensions &spriteBatch)
{
	sprite->Update();
	spriteBatch.Draw(*sprite, position);
}
