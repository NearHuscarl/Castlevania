#pragma once

#include "Direct2DGame/Utilities/Stopwatch.h"
#include "../GameObject.h"

namespace Castlevania
{
	class Powerup : public GameObject
	{
	public:
		Powerup(EntityType type);

		void Spawn();
		void Update(GameTime gameTime, UpdateData &updateData) override;

	private:
		Stopwatch lifespanTimer;
	};
}