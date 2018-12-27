#include "ItemRenderingSystem.h"
#include "../../GameObject.h"

using namespace Castlevania;

ItemRenderingSystem::ItemRenderingSystem(
	GameObject &parent,
	std::string spritePath,
	std::unique_ptr<IEffect> deadEffect,
	std::unique_ptr<IEffect> hitEffect)
	:
	parent{ parent }
{
	this->spritePath = spritePath;
	this->deadEffect = std::move(deadEffect);
	this->hitEffect = std::move(hitEffect);
}

ItemRenderingSystem::ItemRenderingSystem(
	GameObject &parent,
	TextureRegion textureRegion,
	std::unique_ptr<IEffect> deadEffect,
	std::unique_ptr<IEffect> hitEffect)
	:
	parent{ parent }
{
	this->sprite = std::make_unique<Sprite>(textureRegion);
	this->deadEffect = std::move(deadEffect);
	this->hitEffect = std::move(hitEffect);
}

Sprite &ItemRenderingSystem::GetSprite()
{
	return *sprite;
}

GameObject &ItemRenderingSystem::GetParent()
{
	return parent;
}

void ItemRenderingSystem::LoadContent(ContentManager &content)
{
	RenderingSystem::LoadContent(content);

	if (sprite != nullptr)
		return;

	auto texture = content.Load<Texture>(spritePath);
	sprite = std::make_unique<Sprite>(texture);
}

void ItemRenderingSystem::Update(GameTime gameTime)
{
	if (GetParent().GetState() == ObjectState::DYING)
	{
		deadEffect->Update(gameTime);

		if (deadEffect->IsFinished())
			GetParent().Destroy();
	}

	if (hitEffect != nullptr)
		hitEffect->Update(gameTime);
}

void ItemRenderingSystem::Draw(SpriteExtensions &spriteBatch)
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

void ItemRenderingSystem::OnStateChanged()
{
	if (GetParent().GetState() == ObjectState::DYING)
	{
		if (deadEffect != nullptr)
			deadEffect->Show(GetParent().GetOriginPosition());
		else
			GetParent().Destroy();
	}
}

void ItemRenderingSystem::OnTakingDamage()
{
	if (hitEffect != nullptr)
		hitEffect->Show(GetParent().GetOriginPosition());
}
