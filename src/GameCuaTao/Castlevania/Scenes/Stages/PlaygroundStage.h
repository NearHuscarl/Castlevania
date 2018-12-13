#pragma once

#include "Stage.h"

namespace Castlevania
{
	class PlaygroundStage : public Stage
	{
	public:
		PlaygroundStage(GameplayScene &gameplayScene, std::string spawnPoint);

		void Update(GameTime gameTime) override;

	private:
		void UpdateInput();
	};
}