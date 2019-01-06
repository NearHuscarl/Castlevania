#include "Direct2DGame/MathHelper.h"
#include "EntityMovementSystem.h"
#include "../../GameObject.h"
#include "../../Settings.h"

using namespace Castlevania;

EntityMovementSystem::EntityMovementSystem(GameObject &parent, float weight) : parent{ parent }
{
	this->weight = weight;
}

void EntityMovementSystem::UpdateMovement(GameTime gameTime)
{
	auto velocity = parent.GetVelocity();
	auto deltaTime = (float)gameTime.ElapsedGameTime.Seconds();

	velocity.y = MathHelper::Min(velocity.y + GRAVITY, weight);
	parent.SetVelocity(velocity);

	distance = velocity * deltaTime;
}
