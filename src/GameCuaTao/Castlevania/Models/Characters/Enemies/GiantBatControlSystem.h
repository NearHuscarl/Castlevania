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
		float minSpeed;
		float maxSpeed;
		float heightToStopDiving;
		Vector2 playerPosition;

		void OnMoveStateChanged();
		void OnActiveChanged();

		bool IsDistanceOutsideOfViewport(Vector2 distance);
		bool IsBelowPlayer();
		float GetSpeedRelativeToPlayerDistance();

		void MoveRandomly();
		void ClampMoveInArea();
		Vector2 RandomDirection();
	};
}