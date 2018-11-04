#include "GameObject.h"
#include "Direct2DGame/MathHelper.h"

using namespace Castlevania;

// TODO: remove public setters
void GameObject::SetVelocity(float velocity)
{
	this->velocity = velocity;
}

void GameObject::SetRotation(float degrees)
{
	// The X-Y axis in game has the value Y inverted compare to the X-Y axis in math
	// To convert the X-Y axis from math to game, we need to flip the degrees sign because
	//   with sin(θ) = y, sin(-θ) = -y
	//   with cos(θ) = x, cos(θ) = x
	rotation = MathHelper::Degrees2Vector(-degrees);
}

void GameObject::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}

void GameObject::SetPosition(Vector2 position)
{
	this->position = position;
}

Vector2 GameObject::GetOriginPosition()
{
	return Vector2{
		position.x + GetFrameRect().Width() / 2,
		position.y + GetFrameRect().Height() / 2 };
}

Rect GameObject::GetFrameRect()
{
	auto sprite = GetAnimation().GetCurrentFrame().GetSprite();
	auto spriteFrame = sprite.GetSpriteFrame();

	auto rect = Rect{};

	rect.left = (int)position.x;
	rect.top = (int)position.y;
	rect.right = rect.left + spriteFrame.Width();
	rect.bottom = rect.top + spriteFrame.Height();

	return rect;
}

Rect GameObject::GetBoundingBox()
{
	auto sprite = GetAnimation().GetCurrentFrame().GetSprite();
	auto spriteFrame = sprite.GetSpriteBoundary();
	auto spriteBoundary = sprite.GetSpriteBoundary();

	auto rect = Rect{};

	// spriteFrame is usually larger than the spriteBoundary so we need to take account of the offset
	rect.left = (int)position.x + (spriteFrame.X() - spriteBoundary.X());
	rect.top = (int)position.y + (spriteFrame.Y() - spriteBoundary.Y());
	rect.right = rect.left + spriteBoundary.Width();
	rect.bottom = rect.top + spriteBoundary.Height();

	return rect;
}

Animation &GameObject::GetAnimation()
{
	return animations->GetCurrentAnimation();
}

void GameObject::LoadContent(ContentManager &content)
{
}

void GameObject::Update(float deltaTime)
{
}

void GameObject::UpdateDistance(float deltaTime)
{
	position += rotation * velocity * deltaTime;
}

void GameObject::Draw(SpriteBatch &spriteBatch)
{
}

GameObject::~GameObject()
{
}