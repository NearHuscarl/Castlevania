#include "PantherMovementSystem.h"
#include "Direct2DGame/MathHelper.h"
#include "../../Settings.h"

using namespace Castlevania;

constexpr auto WEIGHT = 1000.0f;

PantherMovementSystem::PantherMovementSystem(Panther &parent) : parent{ parent }
{
}

void PantherMovementSystem::Receive(int message)
{
	switch (message)
	{
		case START_FALLING:
			parent.Jump();
			break;

		case START_LANDING:
			parent.Land();
			break;
	}
}

void PantherMovementSystem::Update(GameTime gameTime)
{
	auto velocity = parent.GetVelocity();
	auto deltaTime = (float)gameTime.ElapsedGameTime.Seconds();

	velocity.y = MathHelper::Min(velocity.y + GRAVITY, WEIGHT);
	parent.SetVelocity(velocity);

	distance = velocity * deltaTime;
}
