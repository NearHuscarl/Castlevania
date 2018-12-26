#pragma once

#include "Direct2DGame/Utilities/Stopwatch.h"
#include "../GameObject.h"

namespace Castlevania
{
	class Powerup : public GameObject
	{
	public:
		Powerup(ObjectId type, int lifeSpan = 0);

		void Spawn();
		void Update(UpdateData &updateData) override;

	private:
		Stopwatch lifespanTimer;
		int lifeSpan;
	};
}