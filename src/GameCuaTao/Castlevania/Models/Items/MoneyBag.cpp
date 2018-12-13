#include "MoneyBag.h"

using namespace Castlevania;

MoneyBag::MoneyBag(int money, EntityType type) : Powerup{ type }
{
	this->money = money;
}

int MoneyBag::GetMoney()
{
	SetState(ObjectState::DYING);
	body.Enabled(false);

	return money;
}
