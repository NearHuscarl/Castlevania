#pragma once

#include "Stage.h"

namespace Castlevania
{
	class GreatHallStage : public Stage
	{
	public:
		GreatHallStage(GameplayScene &gameplayScene);

		void OnNotify(Subject &subject, int event) override;
		void Update(GameTime gameTime) override;

	private:
		Door *door; // reference to the door in next room cutscene

		void SetupNextRoomCutscene();
		void UpdateNextRoomCutscene(GameTime gameTime);
	};
}