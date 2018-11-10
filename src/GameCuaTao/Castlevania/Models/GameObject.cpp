﻿#include "GameObject.h"
#include "Direct2DGame/MathHelper.h"

using namespace Castlevania;

GameObject::GameObject(EntityType type)
{
	this->type = type;
}

EntityType GameObject::GetType()
{
	return type;
}

// TODO: remove public setters
void GameObject::SetVelocity(float velocity)
{
	this->velocity = velocity;
}

void GameObject::SetDirection(float degrees)
{
	// The X-Y axis in game has the value Y inverted compare to the X-Y axis in math
	// To convert the X-Y axis from math to game, we need to flip the degrees sign because
	//   with sin(θ) = y, sin(-θ) = -y
	//   with cos(θ) = x, cos(θ) = x
	direction = MathHelper::Degrees2Vector(-degrees);
}

void GameObject::SetPosition(float x, float y)
{
	transform.position.x = x;
	transform.position.y = y;
}

void GameObject::SetPosition(Vector2 position)
{
	SetPosition(position.x, position.y);
}

Vector2 GameObject::GetPosition()
{
	return transform.position;
}

Vector2 GameObject::GetOriginPosition()
{
	return Vector2{
		transform.position.x + GetFrameRect().Width() / 2,
		transform.position.y + GetFrameRect().Height() / 2 };
}

Rect GameObject::GetFrameRect()
{
	return sprite->GetFrameRectangle(transform);
}

Rect GameObject::GetBoundingBox()
{
	return sprite->GetBoundingRectangle(transform);
}

void GameObject::LoadContent(ContentManager &content)
{
}

void GameObject::Update(float deltaTime)
{
}

void GameObject::UpdateDistance(float deltaTime)
{
	transform.position += direction * velocity * deltaTime;
}

void GameObject::Draw(SpriteExtensions &spriteBatch)
{
}

GameObject::~GameObject()
{
}