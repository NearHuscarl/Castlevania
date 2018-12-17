#include "Direct2DGame/MathHelper.h"
#include "Direct2DGame/Input/Keyboard.h"
#include "GameObject.h"
#include "UpdateData.h"
#include "Settings.h"
#include "../Utilities/CppExtensions.h"

using namespace Castlevania;

GameObject::GameObject(ObjectId type) : body{ *this }
{
	this->objectId = type;
}

#pragma region Getters / Setters

ObjectId GameObject::GetId()
{
	return objectId;
}

int GameObject::GetType()
{
	return (int)objectId;
}

void GameObject::SetState(ObjectState state)
{
	this->state = state;
	SendMessageToSystems(STATE_CHANGED);
}

ObjectState GameObject::GetState()
{
	return state;
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

void GameObject::SetDistance_X(float value)
{
	SetDistance(Vector2{ value, GetDistance().y });
}

void GameObject::SetDistance_Y(float value)
{
	SetDistance(Vector2{ GetDistance().x, value });
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

void GameObject::SetDirection(float angle)
{
	// The X-Y axis in game has the value Y inverted compare to the X-Y axis in math
	// To convert the X-Y axis from math to game, we need to flip the degrees sign because
	//   with sin(θ) = y, sin(-θ) = -y
	//   with cos(θ) = x, cos(θ) = x
	auto direction = MathHelper::Degrees2Vector(-angle);
	SetDirection(direction);
}

void GameObject::SetDirection(Vector2 direction)
{
	velocity = direction * speed;
}

float GameObject::GetSpeed()
{
	return speed;
}

void GameObject::SetSpeed(float speed)
{
	this->speed = speed;
}

RectF GameObject::GetFrameRect()
{
	if (GetSprite() == nullptr)
		return RectF::Empty();

	return GetSprite()->GetFrameRectangle(position);
}

RectF GameObject::GetBoundingBox()
{
	if (GetSprite() == nullptr)
		return RectF::Empty();

	return GetSprite()->GetBoundingRectangle(position);
}

Sprite *GameObject::GetSprite()
{
	if (renderingSystem != nullptr)
		return &renderingSystem->GetSprite();
	else
		return nullptr;
}

Facing GameObject::GetFacing()
{
	return facing;
}

void GameObject::SetFacing(Facing facing)
{
	this->facing = facing;
	SendMessageToSystems(FACING_CHANGED);

	if (GetSprite() == nullptr)
		return;

	if (facing == Facing::Left)
		GetSprite()->SetEffect(SpriteEffects::FlipHorizontally);
	else
		GetSprite()->SetEffect(SpriteEffects::None);
}

void GameObject::SetVisibility(bool value)
{
	if (GetSprite() == nullptr)
		return;

	GetSprite()->SetVisibility(value);
}

Body &Castlevania::GameObject::GetBody()
{
	return body;
}

void GameObject::Destroy()
{
	state = ObjectState::DEAD;
}

void GameObject::EnableControl(bool value)
{
	if (controlSystem != nullptr)
		controlSystem->Enabled(value);
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

void GameObject::Attach(std::unique_ptr<IControlSystem> system)
{
	components.push_back(system.get());
	controlSystem = std::move(system);
}

void GameObject::Attach(std::unique_ptr<IMovementSystem> system)
{
	components.push_back(system.get());
	movementSystem = std::move(system);
}

void GameObject::Attach(std::unique_ptr<ICollisionSystem> system)
{
	components.push_back(system.get());
	collisionSystem = std::move(system);
}

void GameObject::Attach(std::unique_ptr<ICollisionResponseSystem> system)
{
	components.push_back(system.get());
	collisionResponseSystem = std::move(system);
}

void GameObject::Attach(std::unique_ptr<IRenderingSystem> system)
{
	components.push_back(system.get());
	renderingSystem = std::move(system);
}

template<>
void GameObject::Detach<IControlSystem>()
{
	RemoveByValue(components, controlSystem.get());
	controlSystem = nullptr;
}

template<>
void GameObject::Detach<IMovementSystem>()
{
	RemoveByValue(components, movementSystem.get());
	movementSystem = nullptr;
}

template<>
void GameObject::Detach<ICollisionSystem>()
{
	RemoveByValue(components, collisionSystem.get());
	collisionSystem = nullptr;
}

template<>
void GameObject::Detach<ICollisionResponseSystem>()
{
	RemoveByValue(components, collisionResponseSystem.get());
	collisionResponseSystem = nullptr;
}

template<>
void GameObject::Detach<IRenderingSystem>()
{
	RemoveByValue(components, renderingSystem.get());
	renderingSystem = nullptr;
}

#pragma endregion

void GameObject::LoadContent(ContentManager &content)
{
	if (renderingSystem != nullptr)
		renderingSystem->LoadContent(content);
}

void GameObject::Update(GameTime gameTime, UpdateData &updateData)
{
	if (!updateData.viewport.TouchesOrIntersects(GetFrameRect())) // TODO: remove after using collision grid
		return;

	auto objectCollection = updateData.objectCollection;

	if (controlSystem != nullptr)
		controlSystem->Update(updateData);

	if (movementSystem != nullptr)
		movementSystem->Update(gameTime);

	if (collisionSystem != nullptr && objectCollection != nullptr)
		collisionSystem->Update(updateData);

	if (collisionResponseSystem != nullptr && objectCollection != nullptr)
		collisionResponseSystem->Update(updateData);

	if (renderingSystem != nullptr)
		renderingSystem->Update(gameTime);

	Move(GetDistance()); // Can move properly now after handling potential collisions with other objects
}

void GameObject::Draw(SpriteExtensions &spriteBatch)
{
	if (renderingSystem != nullptr)
		renderingSystem->Draw(spriteBatch);
}

void GameObject::SendMessageToSystems(int message)
{
	for (auto &component : components)
	{
		component->Receive(message);
	}
}

GameObject &GameObject::NullObject()
{
	static auto nullGameObject = GameObject{ ObjectId::Unknown };
	return nullGameObject;
}

GameObject::~GameObject()
{
}
