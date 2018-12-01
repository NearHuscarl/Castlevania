#include "CourtyardStage.h"
#include "StageEvent.h"
#include "../../Utilities/MapManager.h"

using namespace Castlevania;

auto playerOriginalSpeed = 0.0f;

CourtyardStage::CourtyardStage(GameplayScene &gameplayScene) : Stage{ gameplayScene, Map::COURTYARD }
{
}

void CourtyardStage::OnNotify(Subject &subject, int event)
{
	switch (event)
	{
		//case NEXT_ROOM:
		//	currentState = CourtyardState::NEXT_ROOM_TRANSITION;
		//	break;

		//case NEXT_MAP:
		//	currentState = CourtyardStage::NEXT_ROOM_TRANSITION;
		//	break;

		case TRANSITION_COMPLETED:
			currentState = GameState::PLAYING;
			break;

		case GO_TO_CASTLE:
			SetupGoToCastleTransition();
			break;
	}
}

void CourtyardStage::Update(GameTime gameTime)
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

		case GameState::GO_TO_CASTLE_CUTSCENE:
			// Simon go to castle in courtyard map
			UpdateGoToCastleTransition(gameTime);
			break;
	}
}

void CourtyardStage::UpdateGoToCastleTransition(GameTime gameTime)
{
	UpdateGameObjects(gameTime);
}

void CourtyardStage::SetupGoToCastleTransition()
{
	playerOriginalSpeed = player->GetSpeed();
	player->SetSpeed(playerOriginalSpeed / 2);
	player->EnableControl(false);
	player->WalkRight();

	currentState = GameState::GO_TO_CASTLE_CUTSCENE;
}
