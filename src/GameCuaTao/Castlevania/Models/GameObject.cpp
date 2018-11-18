#include "Direct2DGame/MathHelper.h"
#include "Direct2DGame/Input/Keyboard.h"
#include "GameObject.h"

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

int GameObject::GetType()
{
	return (int)type;
}

Vector2 GameObject::GetPosition()
{
	return position;
}

Vector2 GameObject::GetDistance()
{
	if (movementSystem != nullptr)
	{
		return movementSystem->GetDistance();
	}

	return Vector2::Zero();
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

Vector2 GameObject::GetOriginPosition()
{
	return Vector2{
		position.x + GetFrameRect().Width() / 2,
		position.y + GetFrameRect().Height() / 2 };
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

Body &Castlevania::GameObject::GetBody()
{
	return body;
}

IController *GameObject::GetController()
{
	return controller.get();
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

void GameObject::Move(Vector2 direction)
{
	position += direction;
}

void GameObject::LoadContent(ContentManager &content)
{
}

void GameObject::Update(float deltaTime, ObjectCollection *objectCollection)
{
	if (movementSystem != nullptr)
		movementSystem->Update(deltaTime);

	if (collisionSystem != nullptr)
		collisionSystem->Update(*objectCollection);

	if (collisionResponseSystem != nullptr)
		collisionResponseSystem->Update();
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
	if (type == EntityType::Boundary)
		spriteBatch.Draw(GetBoundingBox(), Color::Blue());
	else if (type == EntityType::Whip)
		spriteBatch.Draw(GetBoundingBox(), Color::Red());
	else if (type == EntityType::FirePit)
		spriteBatch.Draw(GetBoundingBox(), Color::Green());
	else
		spriteBatch.Draw(GetBoundingBox(), Color::Magenta());
}

GameObject::~GameObject()
{
}
