#pragma once

#include "Direct2DGame/GameTime.h"
#include "Cutscene.h"
#include "../../Models/Factories/ObjectCollection.h"

namespace Castlevania
{
	class Stage;

	class GoToCastleCutscene : public Cutscene
	{
	public:
		GoToCastleCutscene(Stage &stage, ObjectCollection &objectCollection);

		void Update(GameTime gameTime);

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