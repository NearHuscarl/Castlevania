#include "Simon.h"
#include "../Settings/Animations.h"

using namespace Castlevania;

void Simon::SetDirection(Direction direction)
{
	this->direction = direction;

	if (direction == Direction::Left)
		this->rotation = Vector2(-1, 0);
	else // Direction::Right
		this->rotation = Vector2(1, 0);
}

void Simon::LoadContent(ContentManager &content)
{
	animations = content.Load<AnimationDict>("Characters/Players/SimonAnimation.xml");
	auto stats = content.Load<CharacterStats>("CharacterStats/Simon.xml");

	currentAnimation = stats->startingAnimation;
	speed = stats->speed; // default velocity
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
	velocity = 0;
	currentAnimation = IDLE_ANIMATION;
}

void Simon::WalkLeft()
{
	state = State::WALKING_LEFT;
	SetDirection(Direction::Left);
	velocity = speed;
	currentAnimation = WALK_ANIMATION;
}

void Simon::WalkRight()
{
	state = State::WALKING_RIGHT;
	SetDirection(Direction::Right);
	velocity = speed;
	currentAnimation = WALK_ANIMATION;
}

void Simon::TurnBackward()
{
	state = State::TURNING_BACKWARD;
	velocity = 0;
	currentAnimation = TURN_BACKWARD_ANIMATION;
}