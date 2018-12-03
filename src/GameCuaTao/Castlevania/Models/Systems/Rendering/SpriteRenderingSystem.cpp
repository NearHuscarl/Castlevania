#include "SpriteRenderingSystem.h"
#include "../../GameObject.h"

using namespace Castlevania;

SpriteRenderingSystem::SpriteRenderingSystem(GameObject &parent, std::string spritePath) :
	parent{ parent }
{
	this->spritePath = spritePath;
}

Sprite &SpriteRenderingSystem::GetSprite()
{
	return *sprite;
}

GameObject &SpriteRenderingSystem::GetParent()
{
	return parent;
}

void SpriteRenderingSystem::LoadContent(ContentManager &content)
{
	RenderingSystem::LoadContent(content);

	auto texture = content.Load<Texture>(spritePath);
	sprite = std::make_unique<Sprite>(texture);
}

void SpriteRenderingSystem::Draw(SpriteExtensions &spriteBatch)
{
	RenderingSystem::Draw(spriteBatch);
	spriteBatch.Draw(*sprite, parent.GetPosition());
}