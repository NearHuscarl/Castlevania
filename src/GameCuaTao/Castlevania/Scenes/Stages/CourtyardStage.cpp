#include "CourtyardStage.h"
#include "StageEvent.h"
#include "../../Utilities/MapManager.h"

using namespace Castlevania;

auto playerOriginalSpeed = 0.0f;

CourtyardStage::CourtyardStage(GameplayScene &gameplayScene, std::string checkpoint) :
	Stage{ gameplayScene, Map::COURTYARD, checkpoint }
{
}

void CourtyardStage::OnNotify(Subject &subject, int event)
{
	switch (event)
	{
		case NEXT_MAP_CUTSCENE_STARTED:
			SetupNextMapCutscene();
			break;

		case NEXT_MAP_CUTSCENE_ENDED:
			player->SetSpeed(playerOriginalSpeed);
			break;

		case GO_TO_CASTLE_CUTSCENE_STARTED:
			SetupGoToCastleCutscene();
			break;
	}
}

void CourtyardStage::Initialize()
{
	Stage::Initialize();

	for (auto &object : objectCollection.triggers)
	{
		if (object->GetTriggerType() == TriggerType::CASTLE_ENTRANCE)
			entranceTrigger = object.get();
	}

	for (auto &object : objectCollection.foregroundObjects)
	{
		if ((EntityType)object->GetType() == EntityType::Castle)
			castle = object.get();
	}
}

void CourtyardStage::Update(GameTime gameTime)
{
	switch (currentState)
	{
		case GameState::PLAYING:
			UpdateGameplay(gameTime);
			break;

		case GameState::NEXT_MAP_CUTSCENE:
			UpdateNextMapCutscene(gameTime);
			break;

		case GameState::GO_TO_CASTLE_CUTSCENE:
			// Simon go to castle in courtyard map
			UpdateGoToCastleCutscene(gameTime);
			break;
	}
}

void CourtyardStage::UpdateGoToCastleCutscene(GameTime gameTime)
{
	UpdateGameObjects(gameTime);

	auto aLittleBit = 5.0f; // TODO: the fuck did I write?

	if (player->GetBoundingBox().right <= entranceTrigger->GetBoundingBox().right - aLittleBit)
	{
		if (player->GetFacing() == Facing::Left)
			player->WalkRight();
		
		castle->SetVisibility(true);
	}
}

void CourtyardStage::SetupGoToCastleCutscene()
{
	playerOriginalSpeed = player->GetSpeed();

	player->SetSpeed(playerOriginalSpeed / 3);
	player->EnableControl(false);

	if (player->GetBoundingBox().right <= entranceTrigger->GetBoundingBox().right)
		player->WalkRight();
	else
		player->WalkLeft();

	nextMapTrigger->Enabled(true);

	currentState = GameState::GO_TO_CASTLE_CUTSCENE;
}
