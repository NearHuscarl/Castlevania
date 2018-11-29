#pragma once

#include "RangedWeapon.h"

namespace Castlevania
{
	class Dagger : public RangedWeapon
	{
	public:
		Dagger();
		void Update(GameTime gameTime, UpdateData &updateData) override;
	};
}