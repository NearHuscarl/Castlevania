#pragma once

#include "Stage.h"

namespace Castlevania
{
	class CourtyardStage : public Stage
	{
	public:
		CourtyardStage(GameplayScene &gameplayScene, std::string spawnPoint);

		void Initialize() override;
		void Update(GameTime gameTime) override;

	private:
		GameObject *castle;
		Trigger *entranceTrigger;
		Trigger *nextMapTrigger;

		void UpdateGoToCastleCutscene(GameTime gameTime);
		void SetupGoToCastleCutscene();
		void ProcessMessage() override;
	};
}