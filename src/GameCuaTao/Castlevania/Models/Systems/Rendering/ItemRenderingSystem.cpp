#include "ItemRenderingSystem.h"
#include "../../GameObject.h"

using namespace Castlevania;

ItemRenderingSystem::ItemRenderingSystem(
	GameObject &parent,
	std::string spritePath,
	std::unique_ptr<IEffect> effect)
	:
	parent{ parent }
{
	this->hitEffect = std::move(effect);
	this->spritePath = spritePath;
}

ItemRenderingSystem::ItemRenderingSystem(
	GameObject &parent,
	TextureRegion textureRegion,
	std::unique_ptr<IEffect> effect)
	:
	parent{ parent }
{
	this->sprite = std::make_unique<Sprite>(textureRegion);
	this->hitEffect = std::move(effect);
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
		if (hitEffect->IsFinished())
			GetParent().Destroy();
	}
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
			hitEffect->Draw(spriteBatch);
			break;
	}
}

void ItemRenderingSystem::OnStateChanged()
{
	if (GetParent().GetState() == ObjectState::DYING)
	{
		hitEffect->Show(GetParent().GetOriginPosition());
	}
}
