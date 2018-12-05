#include "Direct2DGame/MathHelper.h"
#include "WaveMovementSystem.h"
#include "../../GameObject.h"

using namespace Castlevania;

WaveMovementSystem::WaveMovementSystem(GameObject &parent) : parent{ parent }
{
	linearVelocity = parent.GetSpeed();
	angularVelocity = MathHelper::TWO_PI;
}

void WaveMovementSystem::SetMoveAxis(Axis axis)
{
	moveAxis = axis;
}

void WaveMovementSystem::Update(GameTime gameTime)
{
	auto velocity = parent.GetVelocity();
	auto deltaTime = (float)gameTime.ElapsedGameTime.Seconds();

	switch (moveAxis)
	{
		case Axis::X:
			velocity.x = linearVelocity;
			velocity.y = std::sin(angularVelocity);
			break;

		case Axis::Y:
			velocity.x = std::sin(angularVelocity);
			velocity.y = linearVelocity;
			break;
	}

	distance = velocity * deltaTime;
}
