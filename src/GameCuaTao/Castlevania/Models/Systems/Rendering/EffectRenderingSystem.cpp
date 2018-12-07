#include "EffectRenderingSystem.h"
#include "../../GameObject.h"
#include "../../Settings.h"

using namespace Castlevania;

EffectRenderingSystem::EffectRenderingSystem(std::string spriteConfigPath, std::unique_ptr<IEffect> effect)
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
	return GameObject::NullObject();
}

void EffectRenderingSystem::Receive(int message)
{
	switch (message)
	{
		case MOVE_STATE_CHANGED:
			OnMoveStateChanged();
			break;

		case STATE_CHANGED:
			OnStateChanged();
			break;
	}

	switch (message)
	{
		case STATE_CHANGED:
			if (GetParent().GetState() == ObjectState::DYING)
				hitEffect->Show(GetParent().GetOriginPosition());
			break;
	}
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

void EffectRenderingSystem::OnMoveStateChanged()
{
}

void EffectRenderingSystem::OnStateChanged()
{
	if (GetParent().GetState() == ObjectState::DYING)
		hitEffect->Show(GetParent().GetOriginPosition());
}
