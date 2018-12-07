#pragma once

#include "Direct2DGame/Utilities/Stopwatch.h"
#include "../../Systems/Control/ControlSystem.h"
#include "../../../Models/Factories/ObjectFactory.h"
#include "Fishman.h"

namespace Castlevania
{
	class FishmanControlSystem : public ControlSystem
	{
	public:
		FishmanControlSystem(Fishman &parent, ObjectFactory &objectFactory);

		void Receive(int message) override;
		void Update(UpdateData &updateData) override;

	private:
		Fishman &parent;
		FishmanState lastState;
		int shootingInterval; // Start shooting after an interval
		Stopwatch shootingIntervalTimer;
		ObjectFactory &objectFactory;

		void ResetShootingTimer();
	};
}