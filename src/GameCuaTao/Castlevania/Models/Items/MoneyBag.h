#pragma once

#include "Powerup.h"

namespace Castlevania
{
	class MoneyBag : public Powerup
	{
	public:
		MoneyBag(int money, ObjectId type);

		int GetMoney();

	private:
		int money;
	};
}