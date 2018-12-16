#include "Direct2DGame/MathHelper.h"
#include "GiantBatMovementSystem.h"
#include "../../GameObject.h"
#include "../../Settings.h"

using namespace Castlevania;

GiantBatMovementSystem::GiantBatMovementSystem(GiantBat &parent) : parent{ parent }
{
}

void GiantBatMovementSystem::Update(GameTime gameTime)
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
}
