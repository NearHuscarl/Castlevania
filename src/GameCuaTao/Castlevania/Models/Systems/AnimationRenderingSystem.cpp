#include "AnimationRenderingSystem.h"
#include "../AnimatedObject.h"

using namespace Castlevania;

AnimationRenderingSystem::AnimationRenderingSystem(AnimatedObject &parent, std::string spriteConfigPath) :
	parent{ parent }
{
	this->spriteConfigPath = spriteConfigPath;
}

RectF AnimationRenderingSystem::GetBoundingBox()
{
	return sprite->GetBoundingRectangle(parent.GetPosition());
}

AnimatedSprite &AnimationRenderingSystem::GetSprite()
{
	return *sprite;
}

void AnimationRenderingSystem::LoadContent(ContentManager &content)
{
	auto animationFactory = content.Load<AnimationFactory>(spriteConfigPath);
	sprite = std::make_unique<AnimatedSprite>(animationFactory);
}

void AnimationRenderingSystem::Update(float deltaTime)
{
	sprite->Update();
}

void AnimationRenderingSystem::Draw(SpriteExtensions &spriteBatch)
{
	auto facing = parent.GetFacing();

	if (facing == Facing::Left)
		sprite->SetEffect(SpriteEffects::FlipHorizontally);
	else
		sprite->SetEffect(SpriteEffects::None);

	spriteBatch.Draw(*sprite, parent.GetPosition());
}