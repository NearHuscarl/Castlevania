#include "GreatHallStage.h"
#include "StageEvent.h"

using namespace Castlevania;

GreatHallStage::GreatHallStage(GameplayScene &gameplayScene) : Stage{ gameplayScene, Map::GREAT_HALL }
{
}

void GreatHallStage::OnNotify(Subject &subject, int event)
{
	switch (event)
	{
		//case NEXT_ROOM:
		//	currentState = CourtyardState::NEXT_ROOM_TRANSITION;
		//	break;

		case CUTSCENE_COMPLETED:
			currentState = GameState::PLAYING;
			break;
	}
}

void GreatHallStage::Update(GameTime gameTime)
{
	UpdateInput();

	switch (currentState)
	{
		case GameState::PLAYING:
			UpdateGameplay(gameTime);
			break;

		//case CourtyardStage::NEXT_ROOM_CUTSCENE:
		//	// - Viewport stays still
		//	// - Simon goes next to the door
		//	//	- Viewport moves to the middle
		//	//	- Door opens
		//	//	- Simon goes through door
		//	//	- Door closes
		//	//	- Viewport moves to the right
		//	// - stage++
		//	break;
	}
}
