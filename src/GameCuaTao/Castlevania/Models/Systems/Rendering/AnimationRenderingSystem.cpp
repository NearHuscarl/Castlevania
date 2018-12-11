#include "AnimationRenderingSystem.h"
#include "../../GameObject.h"

using namespace Castlevania;

AnimationRenderingSystem::AnimationRenderingSystem(std::string spriteConfigPath)
{
	this->spriteConfigPath = spriteConfigPath;
}

Sprite &AnimationRenderingSystem::GetSprite()
{
	return *sprite;
}

void AnimationRenderingSystem::LoadContent(ContentManager &content)
{
	RenderingSystem::LoadContent(content);
	auto animationFactory = content.Load<AnimationFactory>(spriteConfigPath);
	sprite = std::make_unique<AnimatedSprite>(animationFactory);
}

void AnimationRenderingSystem::Update(GameTime gameTime)
{
	sprite->Update();
}

void AnimationRenderingSystem::Draw(SpriteExtensions &spriteBatch)
{
	RenderingSystem::Draw(spriteBatch);
	spriteBatch.Draw(*sprite, GetParent().GetPosition());
}