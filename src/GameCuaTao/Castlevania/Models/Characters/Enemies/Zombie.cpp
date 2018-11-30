#include "Zombie.h"
#include "../../Settings.h"

using namespace Castlevania;

Zombie::Zombie() : Enemy{ EntityType::Zombie }
{
}

void Zombie::WalkRight()
{
	SetFacing(Facing::Right);
	velocity.x = speed;
}

void Zombie::WalkLeft()
{
	SetFacing(Facing::Left);
	velocity.x = -speed;
}

void Zombie::StopWalking()
{
	velocity = Vector2::Zero();
	SetDistance(Vector2::Zero());
}

void Zombie::Land()
{
	if (facing == Facing::Left)
		WalkLeft();
	else
		WalkRight();
}
