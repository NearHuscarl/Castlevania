#include "UndergroundStage.h"
#include "StageEvent.h"
#include "../../Utilities/MapManager.h"

using namespace Castlevania;

UndergroundStage::UndergroundStage(GameplayScene &gameplayScene, std::string spawnPoint) :
	Stage{ gameplayScene, Map::UNDERGROUND, spawnPoint }
{
}

void UndergroundStage::Update(GameTime gameTime)
{
	switch (currentState)
	{
		case GameState::PLAYING:
			UpdateGameplay(gameTime);
			break;

		case GameState::NEXT_MAP_CUTSCENE:
			UpdateNextMapCutscene(gameTime);
			break;
	}

	Stage::Update(gameTime);
}

void UndergroundStage::ProcessMessage()
{
	if (newEvent == nullptr)
		return;

	switch (newEvent->message)
	{
		case NEXT_MAP_CUTSCENE_STARTED:
			SetupNextMapCutscene();
			break;
	}
}
