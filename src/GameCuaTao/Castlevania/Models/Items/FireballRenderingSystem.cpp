#include "FireballRenderingSystem.h"
#include "../GameObject.h"

using namespace Castlevania;

FireballRenderingSystem::FireballRenderingSystem(
	GameObject &parent,
	std::string spritePath,
	std::unique_ptr<IEffect> effect)
	:
	parent{ parent }
{
	this->hitEffect = std::move(effect);
	this->spritePath = spritePath;
}

Sprite &FireballRenderingSystem::GetSprite()
{
	return *sprite;
}

GameObject &FireballRenderingSystem::GetParent()
{
	return parent;
}

void FireballRenderingSystem::LoadContent(ContentManager &content)
{
	RenderingSystem::LoadContent(content);

	auto texture = content.Load<Texture>(spritePath);
	sprite = std::make_unique<Sprite>(texture);
}

void FireballRenderingSystem::Update(GameTime gameTime)
{
	if (GetParent().GetState() == ObjectState::DYING)
	{
		if (hitEffect->IsFinished())
			GetParent().Destroy();
	}
}

void FireballRenderingSystem::Draw(SpriteExtensions &spriteBatch)
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

void FireballRenderingSystem::OnStateChanged()
{
	if (GetParent().GetState() == ObjectState::DYING)
	{
		hitEffect->Show(GetParent().GetOriginPosition());
	}
}
