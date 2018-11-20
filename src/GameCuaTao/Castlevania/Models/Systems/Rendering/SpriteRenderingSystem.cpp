#include "SpriteRenderingSystem.h"
#include "../../StaticObject.h"

using namespace Castlevania;

SpriteRenderingSystem::SpriteRenderingSystem(StaticObject &parent, std::string spritePath) :
	parent{ parent }
{
	this->spritePath = spritePath;
}

RectF SpriteRenderingSystem::GetBoundingBox()
{
	return sprite->GetBoundingRectangle(parent.GetPosition());
}

Sprite &SpriteRenderingSystem::GetSprite()
{
	return *sprite;
}

void SpriteRenderingSystem::LoadContent(ContentManager &content)
{
	auto texture = content.Load<Texture>(spritePath);
	sprite = std::make_unique<Sprite>(texture);
}

void SpriteRenderingSystem::Update(float deltaTime)
{
}

void SpriteRenderingSystem::Draw(SpriteExtensions &spriteBatch)
{
	spriteBatch.Draw(*sprite, parent.GetPosition());
}