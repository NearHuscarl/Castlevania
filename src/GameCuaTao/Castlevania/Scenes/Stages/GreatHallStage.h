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
	};
}