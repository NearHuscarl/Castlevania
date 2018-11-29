#include "Zombie.h"
#include "ZombieSettings.h"

using namespace Castlevania;

Zombie::Zombie() : Enemy{ EntityType::Zombie }
{
}

void Zombie::SetState(ZombieState state)
{
	this->state = state;
	SendMessageToSystems(STATE_CHANGED);
}

void Zombie::WalkRight()
{
	SetState(ZombieState::WALKING);
	SetFacing(Facing::Right);
	velocity.x = speed;
}

void Zombie::WalkLeft()
{
	SetState(ZombieState::WALKING);
	SetFacing(Facing::Left);
	velocity.x = -speed;
}
