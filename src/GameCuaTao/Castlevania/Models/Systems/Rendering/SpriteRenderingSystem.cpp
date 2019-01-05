#include "SpriteRenderingSystem.h"
#include "../../GameObject.h"

using namespace Castlevania;

SpriteRenderingSystem::SpriteRenderingSystem(GameObject &parent, std::string spritePath) :
	parent{ parent }
{
	this->spritePath = spritePath;
}

SpriteRenderingSystem::SpriteRenderingSystem(GameObject &parent, TextureRegion textureRegion) :
	parent{ parent }
{
	this->sprite = std::make_unique<Sprite>(textureRegion);
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

	if (sprite != nullptr)
		return;

	auto texture = content.Load<Texture>(spritePath);
	sprite = std::make_unique<Sprite>(texture);
}

void SpriteRenderingSystem::Draw(SpriteExtensions &spriteBatch)
{
	spriteBatch.Draw(*sprite, parent.GetPosition());
	RenderingSystem::Draw(spriteBatch);
}