#include "ZombieMovementSystem.h"
#include "Direct2DGame/MathHelper.h"
#include "../../Settings.h"

using namespace Castlevania;

constexpr auto WEIGHT = 1000.0f;

ZombieMovementSystem::ZombieMovementSystem(Zombie &parent) : parent{ parent }
{
}

void ZombieMovementSystem::Receive(int message)
{
	switch (message)
	{
		case START_FALLING:
			parent.StopWalking();
			break;

		case START_LANDING:
			parent.Land();
			break;
	}
}

void ZombieMovementSystem::Update(GameTime gameTime)
{
	auto velocity = parent.GetVelocity();
	auto deltaTime = (float)gameTime.ElapsedGameTime.Seconds();

	velocity.y = MathHelper::Min(velocity.y + GRAVITY, WEIGHT);
	parent.SetVelocity(velocity);

	distance = velocity * deltaTime;
}
