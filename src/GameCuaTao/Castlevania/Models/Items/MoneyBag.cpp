#include "MoneyBag.h"

using namespace Castlevania;

MoneyBag::MoneyBag(int money, ObjectId type) : Powerup{ type }
{
	this->money = money;
}

int MoneyBag::GetMoney()
{
	SetState(ObjectState::DYING);
	body.Enabled(false);

	return money;
}
