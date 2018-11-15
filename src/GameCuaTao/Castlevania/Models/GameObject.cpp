#include "GameObject.h"
#include "Direct2DGame/MathHelper.h"

using namespace Castlevania;

GameObject::GameObject() : GameObject(EntityType::Unknown)
{
}

GameObject::GameObject(EntityType type) :
	body{ *this },
	collisionSystem{ *this }
{
	this->type = type;
}

#pragma region Getters / Setters

EntityType GameObject::GetType()
{
	return type;
}

// TODO: remove public setters
void GameObject::SetVelocity(Vector2 velocity)
{
	this->velocity = velocity;
}

Vector2 GameObject::GetVelocity()
{
	return velocity;
}

void GameObject::SetLinearVelocity(float speed, float angle)
{
	// The X-Y axis in game has the value Y inverted compare to the X-Y axis in math
	// To convert the X-Y axis from math to game, we need to flip the degrees sign because
	//   with sin(θ) = y, sin(-θ) = -y
	//   with cos(θ) = x, cos(θ) = x
	auto direction = MathHelper::Degrees2Vector(-angle);
	velocity = direction * speed;
}

void GameObject::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}

void GameObject::SetPosition(Vector2 position)
{
	SetPosition(position.x, position.y);
}

Vector2 GameObject::GetPosition()
{
	return position;
}

Body Castlevania::GameObject::GetBody()
{
	return body;
}

Vector2 GameObject::GetOriginPosition()
{
	return Vector2{
		position.x + GetFrameRect().Width() / 2,
		position.y + GetFrameRect().Height() / 2 };
}

Rect GameObject::GetFrameRect()
{
	return sprite->GetFrameRectangle(position);
}

Rect GameObject::GetBoundingBox()
{
	return sprite->GetBoundingRectangle(position);
}

#pragma endregion

void GameObject::LoadContent(ContentManager &content)
{
}

void GameObject::Update(float deltaTime, ObjectCollection *objectCollection)
{
	body.Update(deltaTime);
}

void GameObject::UpdateDistance(float deltaTime)
{
	position += velocity * deltaTime;
}

void GameObject::Draw(SpriteExtensions &spriteBatch)
{
}

void GameObject::DrawBoundingBox(SpriteExtensions &spriteBatch)
{
	auto boundingBox = GetBoundingBox();
	spriteBatch.Draw(boundingBox, Color::Pink());
}

GameObject::~GameObject()
{
}