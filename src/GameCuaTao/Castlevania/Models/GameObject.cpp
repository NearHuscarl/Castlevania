#include "GameObject.h"
#include "Direct2DGame/MathHelper.h"

using namespace Castlevania;

GameObject::GameObject() : GameObject(EntityType::Unknown)
{
}

GameObject::GameObject(RectF boundingBox) : GameObject(EntityType::Boundary)
{
	this->boundingBox = std::make_unique<RectF>(boundingBox);
}

GameObject::GameObject(EntityType type) : body{ *this }
{
	this->type = type;
}

#pragma region Getters / Setters

EntityType GameObject::GetType()
{
	return type;
}

Vector2 GameObject::GetPosition()
{
	return position;
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

Vector2 GameObject::GetVelocity()
{
	return velocity;
}

void GameObject::SetVelocity(Vector2 velocity)
{
	this->velocity = velocity;
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

Vector2 GameObject::GetOriginPosition()
{
	return Vector2{
		position.x + GetFrameRect().Width() / 2,
		position.y + GetFrameRect().Height() / 2 };
}

Body Castlevania::GameObject::GetBody()
{
	return body;
}

Rect GameObject::GetFrameRect()
{
	return sprite->GetFrameRectangle(position);
}

RectF GameObject::GetBoundingBox()
{
	if (sprite != nullptr)
		return sprite->GetBoundingRectangle(position);
	
	if (boundingBox != nullptr)
		return *boundingBox;

	return RectF::Empty();
}

void GameObject::SetCollisionSystem(std::unique_ptr<CollisionSystem> collisionSystem)
{
	this->collisionSystem = std::move(collisionSystem);
}

void GameObject::SetCollisionResponseSystem(std::unique_ptr<CollisionResponseSystem> collisionResponseSystem)
{
	this->collisionResponseSystem = std::move(collisionResponseSystem);
}

#pragma endregion

void GameObject::Move(Vector2 direction)
{
	position += direction;
}

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
	spriteBatch.Draw(GetBoundingBox(), Color::Pink());
}

GameObject::~GameObject()
{
}