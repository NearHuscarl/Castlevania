#include "GameObject.h"

GameObject::GameObject()
{
	position = Vector(0, 0);
	velocity = Vector(0, 0);

	direction = 1;	
}

void GameObject::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
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

void GameObject::Update(unsigned long deltaTime)
{
	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;
}

void GameObject::Draw(ISpriteHandler_ spriteHandler)
{
}

GameObject::~GameObject()
{
}