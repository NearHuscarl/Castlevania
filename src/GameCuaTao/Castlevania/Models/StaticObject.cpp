#include "StaticObject.h"

using namespace Castlevania;

StaticObject::StaticObject() : StaticObject(EntityType::Unknown)
{
}

StaticObject::StaticObject(EntityType type) : GameObject(type)
{
}

RectF StaticObject::GetFrameRect()
{
	return GetSprite().GetFrameRectangle(position);
}

RectF StaticObject::GetBoundingBox()
{
	return GetSprite().GetBoundingRectangle(position);
}

Sprite &StaticObject::GetSprite()
{
	return renderingSystem->GetSprite();
}

template<>
void StaticObject::AttachRenderer(std::unique_ptr<ISpriteRenderingSystem> system)
{
	this->renderingSystem = std::move(system);
}

void StaticObject::LoadContent(ContentManager &content)
{
	renderingSystem->LoadContent(content);
}

void StaticObject::Update(float deltaTime, ObjectCollection *objectCollection)
{
	GameObject::Update(deltaTime, objectCollection);

	if (renderingSystem != nullptr)
		renderingSystem->Update(deltaTime);
}

void StaticObject::Draw(SpriteExtensions &spriteBatch)
{
	renderingSystem->Draw(spriteBatch);
}

StaticObject::~StaticObject()
{
}
