#pragma once

#include "Stage.h"

namespace Castlevania
{
	enum class GameState
	{
		PLAYING,
		NEXT_MAP_CUTSCENE,
		NEXT_ROOM_CUTSCENE,
		GO_TO_CASTLE_CUTSCENE,
	};

	class CourtyardStage : public Stage
	{
	public:
		CourtyardStage(GameplayScene &gameplayScene);

		void OnNotify(Subject &subject, int event) override;
		void Update(GameTime gameTime) override;

	private:
		GameState currentState;

		void UpdateGoToCastleTransition(GameTime gameTime);

		void SetupGoToCastleTransition();
	};
}