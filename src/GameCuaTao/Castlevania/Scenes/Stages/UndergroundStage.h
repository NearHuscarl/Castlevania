#pragma once

#include "Stage.h"

namespace Castlevania
{
	class UndergroundStage : public Stage
	{
	public:
		UndergroundStage(GameplayScene &gameplayScene, std::string spawnPoint);

		void Update(GameTime gameTime) override;

	private:
		void ProcessMessage() override;
	};
}