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
		void Update(float deltaTime, ObjectCollection *objectCollection = nullptr) override;

	private:
		Stopwatch lifespanTimer;
	};
}