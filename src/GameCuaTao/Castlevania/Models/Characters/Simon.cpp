#include "Simon.h"
#include "../../Settings/Animations.h"

using namespace Castlevania;

// TODO: use collision detection instead of hardcode GROUND_POSITION_Y
constexpr auto GROUND_POSITION_Y = 100.0f;

Simon::Simon() : Simon(EntityType::Simon)
{
}

Simon::Simon(EntityType type) : GameObject(type)
{
}

void Simon::SetFacing(Facing facing)
{
	this->facing = facing;

	if (facing == Facing::Left)
		this->direction = Vector2{ -1, 0 };
	else // Facing::Right
		this->direction = Vector2{ 1, 0 };
}

void Simon::LoadContent(ContentManager &content)
{
	auto animationFactory = content.Load<AnimationFactory>("Characters/Players/SimonAnimation.xml");
	sprite = std::make_unique<AnimatedSprite>(animationFactory);

	auto stats = content.Load<CharacterStats>("CharacterStats/Simon.xml");
	speed = stats->speed; // default velocity

	Idle();
	facing = Facing::Right;
}

void Simon::Update(float deltaTime)
{
	GameObject::UpdateDistance(deltaTime);

	sprite->Update(deltaTime);
}

void Simon::Draw(SpriteExtensions &spriteBatch)
{
	if (facing == Facing::Right)
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
	SetFacing(Facing::Left);
	velocity = speed;
	sprite->Play(WALK_ANIMATION);
}

void Simon::WalkRight()
{
	state = State::WALKING_RIGHT;
	SetFacing(Facing::Right);
	velocity = speed;
	sprite->Play(WALK_ANIMATION);
}

void Simon::TurnBackward()
{
	state = State::TURNING_BACKWARD;
	velocity = 0;
	sprite->Play(TURN_BACKWARD_ANIMATION);
}