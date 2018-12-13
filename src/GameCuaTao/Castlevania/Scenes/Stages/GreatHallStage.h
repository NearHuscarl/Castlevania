#pragma once

#include "Stage.h"
#include "NextRoomCutscene.h"

namespace Castlevania
{
	class GreatHallStage : public Stage
	{
	public:
		GreatHallStage(GameplayScene &gameplayScene, std::string spawnPoint);
		
		void Update(GameTime gameTime) override;

	private:
		std::unique_ptr<NextRoomCutscene> nextRoomCutscene;

		void SetupNextRoomCutscene();
		void UpdateNextRoomCutscene(GameTime gameTime);
		void OnNextRoomCutsceneComplete();
		void ProcessMessage() override;
	};
}