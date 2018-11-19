#include "AnimatedObject.h"

using namespace Castlevania;

AnimatedObject::AnimatedObject() : AnimatedObject(EntityType::Unknown)
{
}

AnimatedObject::AnimatedObject(EntityType type) : GameObject(type)
{
}

Facing AnimatedObject::GetFacing()
{
	return facing;
}

RectF AnimatedObject::GetFrameRect()
{
	return GetSprite().GetFrameRectangle(position);
}

RectF AnimatedObject::GetBoundingBox()
{
	return GetSprite().GetBoundingRectangle(position);
}

AnimatedSprite &AnimatedObject::GetSprite()
{
	return renderingSystem->GetSprite();
}

template<>
void AnimatedObject::AttachRenderer(std::unique_ptr<IAnimationRenderingSystem> system)
{
	this->renderingSystem = std::move(system);
}

void AnimatedObject::LoadContent(ContentManager &content)
{
	renderingSystem->LoadContent(content);
}

void AnimatedObject::Update(float deltaTime, ObjectCollection *objectCollection)
{
	GameObject::Update(deltaTime, objectCollection);

	if (renderingSystem != nullptr)
		renderingSystem->Update(deltaTime);
}

void AnimatedObject::Draw(SpriteExtensions &spriteBatch)
{
	renderingSystem->Draw(spriteBatch);
}

AnimatedObject::~AnimatedObject()
{
}
