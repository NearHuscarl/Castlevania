#include "Direct2DGame/MathHelper.h"
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
	return GetSprite().GetFrameRectangle(position);
}

RectF GameObject::GetBoundingBox()
{
	if (!body.Enabled())
		return RectF::Empty();

	return GetSprite().GetBoundingRectangle(position);
}

Sprite &GameObject::GetSprite()
{
	return renderingSystem->GetSprite();
}

Facing GameObject::GetFacing()
{
	return facing;
}

void GameObject::SetFacing(Facing facing)
{
	if (this->facing == facing)
		return;

	this->facing = facing;

	if (facing == Facing::Left)
		GetSprite().SetEffect(SpriteEffects::FlipHorizontally);
	else
		GetSprite().SetEffect(SpriteEffects::None);
}

void GameObject::SetVisibility(bool value)
{
	GetSprite().SetIsVisible(value);
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

void GameObject::Move(Vector2 direction)
{
	position += direction;
}

void GameObject::SwitchFacing()
{
	if (facing == Facing::Left)
		SetFacing(Facing::Right);
	else if (facing == Facing::Right)
		SetFacing(Facing::Left);
}

template<>
void GameObject::Attach(std::unique_ptr<IControlSystem> system)
{
	components.push_back(system.get());
	this->controlSystem = std::move(system);
}

template<>
void GameObject::Attach(std::unique_ptr<IMovementSystem> system)
{
	components.push_back(system.get());
	this->movementSystem = std::move(system);
}

template<>
void GameObject::Attach(std::unique_ptr<ICollisionSystem> system)
{
	components.push_back(system.get());
	this->collisionSystem = std::move(system);
}

template<>
void GameObject::Attach(std::unique_ptr<ICollisionResponseSystem> system)
{
	components.push_back(system.get());
	this->collisionResponseSystem = std::move(system);
}

template<>
void GameObject::Attach(std::unique_ptr<IRenderingSystem> system)
{
	components.push_back(system.get());
	this->renderingSystem = std::move(system);
}

#pragma endregion

void GameObject::LoadContent(ContentManager &content)
{
	renderingSystem->LoadContent(content);
}

void GameObject::Update(GameTime gameTime, UpdateData &updateData)
{
	auto objectCollection = updateData.objectCollection;

	if (controlSystem != nullptr)
		controlSystem->Update();

	if (movementSystem != nullptr)
		movementSystem->Update(gameTime);

	if (collisionSystem != nullptr && objectCollection != nullptr)
		collisionSystem->Update(*objectCollection);

	if (collisionResponseSystem != nullptr && objectCollection != nullptr)
		collisionResponseSystem->Update(*objectCollection);

	if (renderingSystem != nullptr)
		renderingSystem->Update(gameTime);

	Move(GetDistance()); // Can move properly now after handling potential collisions with other objects
}

void GameObject::Draw(SpriteExtensions &spriteBatch)
{
	renderingSystem->Draw(spriteBatch);
}

void GameObject::DrawBoundingBox(SpriteExtensions &spriteBatch)
{
	switch (type)
	{
		case EntityType::Whip:
			SpriteHelper::DrawRectangle(spriteBatch, GetBoundingBox(), Color::Red() * 0.75f);
			break;

		case EntityType::FirePit:
			SpriteHelper::DrawRectangle(spriteBatch, GetBoundingBox(), Color::Green() * 0.75f);
			break;

		case EntityType::Player:
			SpriteHelper::DrawRectangle(spriteBatch, GetBoundingBox(), Color::LavenderBlue() * 0.75f);
			break;

		default:
			SpriteHelper::DrawRectangle(spriteBatch, GetBoundingBox(), Color::Magenta() * 0.75f);
			break;
	}
}

void GameObject::SendMessageToSystems(int message)
{
	for (auto &component : components)
	{
		component->Receive(message);
	}
}

GameObject::~GameObject()
{
}
