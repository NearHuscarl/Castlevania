#pragma once

#include "Stage.h"

namespace Castlevania
{
	class CourtyardStage : public Stage
	{
	public:
		CourtyardStage(GameplayScene &gameplayScene);

		void OnNotify(Subject &subject, int event) override;
		void Initialize() override;
		void Update(GameTime gameTime) override;

	private:
		Trigger *entranceTrigger;
		GameObject *castle;

		void UpdateGoToCastleCutscene(GameTime gameTime);
		void SetupGoToCastleCutscene();
	};
}