#include "EffectRenderingSystem.h"
#include "../../GameObject.h"
#include "../../Settings.h"

using namespace Castlevania;

EffectRenderingSystem::EffectRenderingSystem(
	GameObject &parent,
	std::string spriteConfigPath,
	std::unique_ptr<IEffect> effect)
	:
	parent{ parent }
{
	this->hitEffect = std::move(effect);
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
			if (hitEffect->IsFinished())
				GetParent().Destroy();
			break;
	}
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
			hitEffect->Draw(spriteBatch);
			break;
	}
}

void EffectRenderingSystem::OnStateChanged()
{
	if (GetParent().GetState() == ObjectState::DYING)
	{
		hitEffect->Show(GetParent().GetOriginPosition());
	}
}
