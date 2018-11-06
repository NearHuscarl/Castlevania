#include "Simon.h"
#include "../Settings/Animations.h"

using namespace Castlevania;

void Simon::SetDirection(Direction direction)
{
	this->direction = direction;

	if (direction == Direction::Left)
		this->directionVec = Vector2(-1, 0);
	else // Direction::Right
		this->directionVec = Vector2(1, 0);
}

void Simon::LoadContent(ContentManager &content)
{
	auto animationFactory = content.Load<AnimationFactory>("Characters/Players/SimonAnimation.xml");
	sprite = std::make_unique<AnimatedSprite>(animationFactory);

	auto stats = content.Load<CharacterStats>("CharacterStats/Simon.xml");
	speed = stats->speed; // default velocity

	Idle();
}

void Simon::Update(float deltaTime)
{
	GameObject::UpdateDistance(deltaTime);

	sprite->Update(deltaTime);
}

void Simon::Draw(SpriteExtensions &spriteBatch)
{
	if (direction == Direction::Right)
		sprite->SetEffect(SpriteEffects::None);
	else
		sprite->SetEffect(SpriteEffects::FlipHorizontally);

	spriteBatch.Draw(*sprite, transform);
}

void Simon::Idle()
{
	state = State::IDLE;
	velocity = 0;
	sprite->Play(IDLE_ANIMATION);
}

void Simon::WalkLeft()
{
	state = State::WALKING_LEFT;
	SetDirection(Direction::Left);
	velocity = speed;
	sprite->Play(WALK_ANIMATION);
}

void Simon::WalkRight()
{
	state = State::WALKING_RIGHT;
	SetDirection(Direction::Right);
	velocity = speed;
	sprite->Play(WALK_ANIMATION);
}

void Simon::TurnBackward()
{
	state = State::TURNING_BACKWARD;
	velocity = 0;
	sprite->Play(TURN_BACKWARD_ANIMATION);
}