#include "AnimationRenderingSystem.h"
#include "../../GameObject.h"

using namespace Castlevania;

AnimationRenderingSystem::AnimationRenderingSystem(GameObject &parent, std::string spriteConfigPath) :
	parent{ parent }
{
	this->spriteConfigPath = spriteConfigPath;
}

RectF AnimationRenderingSystem::GetBoundingBox()
{
	return sprite->GetBoundingRectangle(parent.GetPosition());
}

Sprite &AnimationRenderingSystem::GetSprite()
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
	spriteBatch.Draw(*sprite, parent.GetPosition());
}