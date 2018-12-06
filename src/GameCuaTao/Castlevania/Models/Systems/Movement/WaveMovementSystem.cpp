#include "Direct2DGame/MathHelper.h"
#include "WaveMovementSystem.h"
#include "../../GameObject.h"
#include "../../Settings.h"

using namespace Castlevania;

WaveMovementSystem::WaveMovementSystem(GameObject &parent, float angularVelocity, float amplitude, Axis axis) : parent{ parent }
{
	auto speed = parent.GetSpeed();
	if (parent.GetFacing() == Facing::Right)
		this->linearVelocity = speed;
	else
		this->linearVelocity = -speed;

	this->angularVelocity = angularVelocity;
	this->angularRotation = 0.0f;
	this->amplitude = amplitude;
	this->moveAxis = axis;
}

void WaveMovementSystem::SetMoveAxis(Axis axis)
{
	moveAxis = axis;
}

void WaveMovementSystem::Receive(int message)
{
	switch (message)
	{
		case FACING_CHANGED:
		{
			auto speed = parent.GetSpeed();
			if (parent.GetFacing() == Facing::Right)
				this->linearVelocity = speed;
			else
				this->linearVelocity = -speed;
			break;
		}
	}
}

void WaveMovementSystem::Update(GameTime gameTime)
{
	auto velocity = Vector2{};
	auto deltaTime = (float)gameTime.ElapsedGameTime.Seconds();
	
	// https://en.wikipedia.org/wiki/Amplitude
	// φ - Angular rotation
	// ω - Angular velocity
	// t - time
	// K - arbitrary constants representing time offset
	// A - Amplitude (or peak amplitude)
	// y - Oscillating variable

	// φ = ω * (t - K)
	angularRotation += angularVelocity * (deltaTime * 1000);
	// y = A × sin(ω * t)
	auto oscillatingDistance = amplitude * std::sin(MathHelper::ToRadians(angularRotation));
	auto linearDistance = linearVelocity * deltaTime;

	switch (moveAxis)
	{
		case Axis::X:
			distance.x = linearDistance;
			distance.y = oscillatingDistance;
			break;

		case Axis::Y:
			distance.y = linearDistance;
			distance.x = oscillatingDistance;
			break;
	}
}
