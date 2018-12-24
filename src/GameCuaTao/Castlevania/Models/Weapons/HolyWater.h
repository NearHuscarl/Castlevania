#pragma once

#include "Direct2DGame/Utilities/Stopwatch.h"
#include "RangedWeapon.h"

namespace Castlevania
{
	class HolyWater : public RangedWeapon
	{
	public:
		HolyWater();

		void StartFlaming();
		bool IsFlaming();

		void Update(UpdateData &updateData) override;

	private:
		bool isFlaming;
		Stopwatch flamingTimer;
	};
}