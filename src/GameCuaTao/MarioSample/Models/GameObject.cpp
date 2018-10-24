#include "GameObject.h"

using namespace MarioSample;

GameObject::GameObject()
{
	position = Vector(0, 0);
	velocity = Vector(0, 0);

	direction = Right;
}

void GameObject::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;

	direction = Right;
}

void GameObject::SetSpeed(float x, float y)
{
	velocity.x = x;
	velocity.y = y;
}

void GameObject::SetState(int state)
{
	this->state = state;
}

int GameObject::GetState()
{
	return state;
}

void GameObject::UpdateInput()
{
}

void GameObject::Update(float deltaTime)
{
}

void GameObject::UpdateDistance(float deltaTime)
{
	position += velocity * deltaTime;
}

void GameObject::Draw(SpriteBatch &spriteBatch)
{
}

GameObject::~GameObject()
{
}