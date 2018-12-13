#pragma once

#include "Powerup.h"

namespace Castlevania
{
	class MoneyBag : public Powerup
	{
	public:
		MoneyBag(int money, EntityType type);

		int GetMoney();

	private:
		int money;
	};
}