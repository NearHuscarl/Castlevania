#pragma once

#include "Cutscene.h"

namespace Castlevania
{
	class Stage;

	class GoToCastleCutscene : public Cutscene
	{
	public:
		GoToCastleCutscene(Stage &stage, StageObject &stageObject, CollisionGrid &grid, Player &player);

		void Update(UpdateData &updateData);

	private:
		enum class State;

		Player *player;
		Trigger *entranceTrigger;
		Trigger *nextMapTrigger;
		GameObject *castle;

		State currentState;
		float playerOriginalSpeed;

		void SetupCutscene();
	};
}