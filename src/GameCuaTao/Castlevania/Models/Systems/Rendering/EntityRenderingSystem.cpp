#include "EntityRenderingSystem.h"
#include "../../GameObject.h"
#include "../../Settings.h"

using namespace Castlevania;

EntityRenderingSystem::EntityRenderingSystem(
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

Sprite &EntityRenderingSystem::GetSprite()
{
	return *sprite;
}

GameObject &EntityRenderingSystem::GetParent()
{
	return parent;
}

void EntityRenderingSystem::LoadContent(ContentManager &content)
{
	RenderingSystem::LoadContent(content);
	auto animationFactory = content.Load<AnimationFactory>(spriteConfigPath);
	sprite = std::make_unique<AnimatedSprite>(animationFactory);
}

void EntityRenderingSystem::Update(GameTime gameTime)
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

void EntityRenderingSystem::Draw(SpriteExtensions &spriteBatch)
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

void EntityRenderingSystem::OnStateChanged()
{
	if (GetParent().GetState() == ObjectState::DYING)
	{
		if (deadEffect != nullptr)
			deadEffect->Show(GetParent().GetOriginPosition());
		else
			GetParent().Destroy();
	}
}

void EntityRenderingSystem::OnTakingDamage()
{
	if (hitEffect != nullptr)
		hitEffect->Show(GetParent().GetOriginPosition());
}
