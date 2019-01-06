#include "Direct2DGame/MathHelper.h"
#include "GiantBatMovementSystem.h"
#include "../../GameObject.h"
#include "../../Settings.h"

using namespace Castlevania;

GiantBatMovementSystem::GiantBatMovementSystem(GiantBat &parent) : parent{ parent }
{
}

void GiantBatMovementSystem::Receive(int message)
{
	switch (message)
	{
		case MOVE_STATE_CHANGED:
			OnMoveStateChanged();
			break;

		case FACING_CHANGED:
			if (parent.GetFacing() == Facing::Left)
				direction = -1;
			else
				direction = 1;
			parent.velocity.x = -parent.velocity.x;
			break;
	}
}

void GiantBatMovementSystem::OnMoveStateChanged()
{
	switch (parent.GetGiantBatState())
	{
		case GiantBatState::DIVING:
			vertex = parent.playerPosition;
			auto entryPoint = parent.GetPosition();
			
			// https://www.mathwarehouse.com/geometry/parabola/standard-and-vertex-form.php
			// parabola equation (vertex form)
			// y = a(x - h)^2 + k
			//
			// a      - coefficient
			// (x, y) - GiantBat starting position
			// (h, k) - vertex position, in this case the player position
			auto x = entryPoint.x;
			auto y = entryPoint.y;
			auto h = vertex.x;
			auto k = vertex.y;

			a = (y - k) / pow((x - h), 2);

			if (h < x)
			{
				direction = -1;
				parent.SetFacing(Facing::Left);
			}
			else
			{
				direction = 1;
				parent.SetFacing(Facing::Right);
			}

			// Calculate speed in the x axis
			auto dy = k - y;
			auto dx = h - x;
			auto angle = std::atan(dy / dx);
			auto speed = parent.GetDiveSpeed();

			speed_x = speed * std::cos(angle);
			break;
	}
}

void GiantBatMovementSystem::UpdateMovement(GameTime gameTime)
{
	auto deltaTime = (float)gameTime.ElapsedGameTime.Seconds();

	switch (parent.GetGiantBatState())
	{
		case GiantBatState::DIVING:
			UpdateParabolicMovement(deltaTime);
			break;

		default:
			UpdateLinearMovement(deltaTime);
			break;
	}
}

void GiantBatMovementSystem::UpdateLinearMovement(float deltaTime)
{
	auto velocity = parent.GetVelocity();

	distance = velocity * deltaTime;
}

void GiantBatMovementSystem::UpdateParabolicMovement(float deltaTime)
{
	auto position = parent.GetPosition();

	auto x = position.x + (direction * speed_x * deltaTime);
	auto h = vertex.x;
	auto k = vertex.y;
	auto y = a * pow((x - h), 2) + k;

	auto newPosition = Vector2{ x, y };
	
	distance = newPosition - position;

	auto velocity = distance / deltaTime;
	parent.SetVelocity(velocity);
}
