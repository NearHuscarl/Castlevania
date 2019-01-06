#pragma once

#include "Cutscene.h"
#include "../GameplayData.h"
#include "../../Models/Factories/ObjectFactory.h"

namespace Castlevania
{
	class LevelCompletedCutscene : public Cutscene
	{
	public:
		LevelCompletedCutscene(
			Stage &stage,
			CollisionGrid &grid,
			ObjectFactory &objectFactory,
			Player &player,
			GameplayData &gameplayData);
		
		void Update(UpdateData &updateData) override;

	private:
		enum class State;

		Player &player;
		GameplayData &gameplayData;
		State currentState;
		GameObject *crystalBall;
		Stopwatch transitionTimer;
		Stopwatch scoreUpdateTimer;
	};
}