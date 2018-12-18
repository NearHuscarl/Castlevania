#include "EffectRenderingSystem.h"
#include "../../GameObject.h"
#include "../../Settings.h"

using namespace Castlevania;

EffectRenderingSystem::EffectRenderingSystem(
	GameObject &parent,
	std::string spriteConfigPath,
	std::unique_ptr<IEffect> deadEffect,
	std::unique_ptr<IEffect> hitEffect)
	:
	parent{ parent }
{
	this->deadEffect = std::move(deadEffect);
	this->hitEffect = std::move(hitEffect);
	this->spriteConfigPath = spriteConfigPath;
}

Sprite &EffectRenderingSystem::GetSprite()
{
	return *sprite;
}

GameObject &Castlevania::EffectRenderingSystem::GetParent()
{
	return parent;
}

void EffectRenderingSystem::LoadContent(ContentManager &content)
{
	RenderingSystem::LoadContent(content);
	auto animationFactory = content.Load<AnimationFactory>(spriteConfigPath);
	sprite = std::make_unique<AnimatedSprite>(animationFactory);
}

void EffectRenderingSystem::Update(GameTime gameTime)
{
	switch (GetParent().GetState())
	{
		case ObjectState::NORMAL:
			sprite->Update();
			break;

		case ObjectState::DYING:
			deadEffect->Update(gameTime);

			if (deadEffect->IsFinished())
				GetParent().Destroy();
			break;
	}

	if (hitEffect != nullptr)
		hitEffect->Update(gameTime);
}

void EffectRenderingSystem::Draw(SpriteExtensions &spriteBatch)
{
	switch (GetParent().GetState())
	{
		case ObjectState::NORMAL:
			spriteBatch.Draw(*sprite, GetParent().GetPosition());
			RenderingSystem::Draw(spriteBatch);
			break;

		case ObjectState::DYING:
			deadEffect->Draw(spriteBatch);
			break;
	}

	if (hitEffect != nullptr)
		hitEffect->Draw(spriteBatch);
}

void EffectRenderingSystem::OnStateChanged()
{
	if (GetParent().GetState() == ObjectState::DYING)
	{
		deadEffect->Show(GetParent().GetOriginPosition());
	}
}

void EffectRenderingSystem::OnTakingDamage()
{
	hitEffect->Show(GetParent().GetOriginPosition());
}
