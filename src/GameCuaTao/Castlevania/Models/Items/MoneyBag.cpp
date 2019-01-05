#include "MoneyBag.h"

using namespace Castlevania;

MoneyBag::MoneyBag(int money, ObjectId type) : Powerup{ type }
{
	this->money = money;
}

int MoneyBag::GetMoney()
{
	SetState(ObjectState::DYING);

	// Detach movement system so the money bag doesnt move at all
	// If the money bag moves, it will fall through the floor and goes
	// outside collision grid since collision is disabled
	Detach<IMovementSystem>();
	body.Enabled(false);

	return money;
}
