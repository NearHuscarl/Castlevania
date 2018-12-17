#pragma once

#include "../../Systems/Control/ControlSystem.h"
#include "../../../Models/Factories/ObjectFactory.h"
#include "GiantBat.h"

namespace Castlevania
{
	class GiantBatControlSystem : public ControlSystem
	{
	public:
		GiantBatControlSystem(GiantBat &parent, ObjectFactory &objectFactory);

		void Receive(int message) override;
		void Update(UpdateData &updateData) override;

	private:
		GiantBat &parent;
		ObjectFactory &objectFactory;

		int hoveringTime;
		Stopwatch hoveringTimer;
		float originalSpeed; // the closer the player is the quicker to boss moves
		float heightToStopDiving;
		bool isBelowPlayer;

		void OnMoveStateChanged();
		void OnActiveChanged();

		bool IsDistanceOutsideOfViewport(Vector2 distance);
		void MoveRandomly();
		Vector2 RandomDirection();
	};
}