#include "UndergroundStage.h"
#include "StageEvent.h"
#include "../../Utilities/MapManager.h"

using namespace Castlevania;

UndergroundStage::UndergroundStage(GameplayScene &gameplayScene) : Stage{ gameplayScene, Map::UNDERGROUND }
{
}

void UndergroundStage::OnNotify(Subject &subject, int event)
{
	switch (event)
	{
		case NEXT_MAP_CUTSCENE_STARTED:
			SetupNextMapCutscene();
			break;
	}
}

void UndergroundStage::Update(GameTime gameTime)
{
	UpdateInput();

	switch (currentState)
	{
		case GameState::PLAYING:
			UpdateGameplay(gameTime);
			break;

		case GameState::NEXT_MAP_CUTSCENE:
			UpdateNextMapCutscene(gameTime);
			break;
	}
}
