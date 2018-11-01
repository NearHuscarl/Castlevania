#include "GameObject.h"

using namespace MarioSample;

GameObject::GameObject()
{
	position = Vector2::Zero();
	velocity = Vector2::Zero();

	direction = Direction::Right;
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

void GameObject::LoadContent(ContentManager &content)
{
}

void GameObject::Update(float deltaTime)
{
}

void GameObject::UpdateDistance(float deltaTime)
{
	position += velocity * deltaTime;
}

Animation &GameObject::GetAnimation()
{
	return (*animations)[currentAnimation];
}

void GameObject::Draw(SpriteBatch &spriteBatch)
{
}