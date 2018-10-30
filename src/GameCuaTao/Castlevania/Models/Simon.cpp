#include "Simon.h"
#include "SimonSettings.h"

using namespace Castlevania;

void Simon::LoadContent(ContentManager &content)
{
	animations = content.Load<AnimationDict>("Textures/Object/SimonAnimation.xml");
	Idle();
}

void Simon::Update(float deltaTime)
{
	GameObject::UpdateDistance(deltaTime);

	GetAnimation().Update();
}

void Simon::Draw(SpriteBatch &spriteBatch)
{
	auto effect = SpriteEffects{};

	if (direction == Direction::Right)
		effect = SpriteEffects::None;
	else
		effect = SpriteEffects::FlipHorizontally;

	GetAnimation().Draw(spriteBatch, position, Color::White(), effect);
}

void Simon::Idle()
{
	state = State::IDLE;
	velocity.x = 0;
	currentAnimation = IDLE_ANIMATION;
}

void Simon::WalkLeft()
{
	state = State::WALKING_LEFT;
	direction = Direction::Left;
	velocity.x = -WALKING_SPEED;
	currentAnimation = WALK_ANIMATION;
}

void Simon::WalkRight()
{
	state = State::WALKING_RIGHT;
	direction = Direction::Right;
	velocity.x = WALKING_SPEED;
	currentAnimation = WALK_ANIMATION;
}

void Simon::TurnBackward()
{
	state = State::TURNING_BACKWARD;
	velocity.x = 0;
	currentAnimation = TURN_BACKWARD_ANIMATION;
}