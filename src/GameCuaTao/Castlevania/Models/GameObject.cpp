﻿#include "Direct2DGame/MathHelper.h"
#include "Direct2DGame/Input/Keyboard.h"
#include "../Utilities/SpriteHelper.h"
#include "GameObject.h"

using namespace Castlevania;

GameObject::GameObject(EntityType type) : body{ *this }
{
	this->type = type;
}

#pragma region Getters / Setters

int GameObject::GetType()
{
	return (int)type;
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

Vector2 GameObject::GetDistance()
{
	if (movementSystem != nullptr)
		return movementSystem->GetDistance();

	return Vector2::Zero();
}

void GameObject::SetDistance(Vector2 distance)
{
	if (movementSystem != nullptr)
		return movementSystem->SetDistance(distance);
}

Vector2 GameObject::GetOriginPosition()
{
	return Vector2{
		position.x + GetFrameRect().Width() / 2,
		position.y + GetFrameRect().Height() / 2 };
}

void GameObject::SetOriginPosition(Vector2 value)
{
	position = Vector2{
		value.x - GetFrameRect().Width() / 2,
		value.y - GetFrameRect().Height() / 2 };
}

Vector2 GameObject::GetVelocity()
{
	return velocity;
}

void GameObject::SetVelocity(Vector2 velocity)
{
	this->velocity = velocity;
}

void GameObject::SetVelocity_X(float x)
{
	velocity.x = x;
}

void GameObject::SetVelocity_Y(float y)
{
	velocity.y = y;
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

RectF GameObject::GetFrameRect()
{
	return RectF::Empty();
}

RectF GameObject::GetBoundingBox()
{
	return RectF::Empty();
}

Body &Castlevania::GameObject::GetBody()
{
	return body;
}

void GameObject::Destroy()
{
	isDestroyed = true;
}

bool GameObject::IsDestroyed()
{
	return isDestroyed;
}

IController *GameObject::GetController()
{
	return controller.get();
}

void GameObject::Move(Vector2 direction)
{
	position += direction;
}

template<>
void GameObject::Attach(std::unique_ptr<IController> system)
{
	this->controller = std::move(system);
	Keyboard::Register(controller.get());
}

template<>
void GameObject::Attach(std::unique_ptr<IMovementSystem> system)
{
	this->movementSystem = std::move(system);
}

template<>
void GameObject::Attach(std::unique_ptr<ICollisionSystem> system)
{
	this->collisionSystem = std::move(system);
}

template<>
void GameObject::Attach(std::unique_ptr<ICollisionResponseSystem> system)
{
	this->collisionResponseSystem = std::move(system);
}

#pragma endregion

void GameObject::LoadContent(ContentManager &content)
{
}

void GameObject::Update(float deltaTime, ObjectCollection *objectCollection)
{
	if (movementSystem != nullptr)
		movementSystem->Update(deltaTime);

	if (collisionSystem != nullptr && objectCollection != nullptr)
		collisionSystem->Update(*objectCollection);

	if (collisionResponseSystem != nullptr && objectCollection != nullptr)
		collisionResponseSystem->Update(*objectCollection);

	Move(GetDistance()); // Can move properly now after handling potential collisions with other objects
}

void GameObject::Draw(SpriteExtensions &spriteBatch)
{
}

void GameObject::DrawBoundingBox(SpriteExtensions &spriteBatch)
{
	switch (type)
	{
		case EntityType::Boundary:
			SpriteHelper::DrawRectangle(spriteBatch, GetBoundingBox(), Color::Blue());
			break;

		case EntityType::Whip:
			SpriteHelper::DrawRectangle(spriteBatch, GetBoundingBox(), Color::Red());
			break;

		case EntityType::FirePit:
			SpriteHelper::DrawRectangle(spriteBatch, GetBoundingBox(), Color::Green());
			break;

		case EntityType::Player:
			SpriteHelper::DrawRectangle(spriteBatch, GetBoundingBox(), Color::LavenderBlue());
			break;

		default:
			SpriteHelper::DrawRectangle(spriteBatch, GetBoundingBox(), Color::Magenta());
			break;
	}
}

GameObject::~GameObject()
{
}
