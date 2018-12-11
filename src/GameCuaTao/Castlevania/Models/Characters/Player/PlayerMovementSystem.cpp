#include "Direct2DGame/MathHelper.h"
#include "PlayerMovementSystem.h"
#include "../../Settings.h"
#include "../../GameObject.h"

using namespace Castlevania;

constexpr auto WEIGHT = 1000.0f;
constexpr auto HOVERING_GRAVITY = GRAVITY / 6;

PlayerMovementSystem::PlayerMovementSystem(Player &parent) : parent{ parent }
{
}

void PlayerMovementSystem::Update(GameTime gameTime)
{
	auto velocity = parent.GetVelocity();
	auto deltaTime = (float)gameTime.ElapsedGameTime.Seconds();
	auto moveState = parent.GetMoveState();

	if (!parent.IsOnStairs())
	{
		if (parent.GetMoveState() == MoveState::HOVERING)
			velocity.y = MathHelper::Min(velocity.y + HOVERING_GRAVITY, WEIGHT);
		else
			velocity.y = MathHelper::Min(velocity.y + GRAVITY, WEIGHT);
	}

	parent.SetVelocity(velocity);

	distance = velocity * deltaTime;
}
