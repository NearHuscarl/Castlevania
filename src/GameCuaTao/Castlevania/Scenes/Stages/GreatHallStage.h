#pragma once

#include "Stage.h"
#include "NextRoomCutscene.h"

namespace Castlevania
{
	class GreatHallStage : public Stage
	{
	public:
		GreatHallStage(GameplayScene &gameplayScene, std::string checkpoint);

		void OnNotify(Subject &subject, int event) override;
		void Update(GameTime gameTime) override;

	private:
		int newMessage;
		std::unique_ptr<NextRoomCutscene> nextRoomCutscene;

		void SetupNextRoomCutscene();
		void OnNextRoomCutsceneComplete();
		void UpdateNextRoomCutscene(GameTime gameTime);
		void ProcessMessage();
	};
}