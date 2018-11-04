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
	animations = content.Load<AnimationSet>("Characters/Players/SimonAnimation.xml");
	auto stats = content.Load<CharacterStats>("CharacterStats/Simon.xml");

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
	animations->Play(IDLE_ANIMATION);
}

void Simon::WalkLeft()
{
	state = State::WALKING_LEFT;
	SetDirection(Direction::Left);
	velocity = speed;
	animations->Play(WALK_ANIMATION);
}

void Simon::WalkRight()
{
	state = State::WALKING_RIGHT;
	SetDirection(Direction::Right);
	velocity = speed;
	animations->Play(WALK_ANIMATION);
}

void Simon::TurnBackward()
{
	state = State::TURNING_BACKWARD;
	velocity = 0;
	animations->Play(TURN_BACKWARD_ANIMATION);
}