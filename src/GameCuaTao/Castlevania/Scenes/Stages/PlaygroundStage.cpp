#include "Direct2DGame/Input/InputHelper.h"
#include "PlaygroundStage.h"
#include "../GameplayScene.h"

using namespace Castlevania;

PlaygroundStage::PlaygroundStage(GameplayScene &gameplayScene, std::string spawnPoint) :
	Stage{ gameplayScene, Map::PLAYGROUND, spawnPoint }
{
}

void PlaygroundStage::Update(GameTime gameTime)
{
	UpdateInput();
	UpdateGameplay(gameTime);

	Stage::Update(gameTime);
}

void PlaygroundStage::UpdateInput()
{
	auto locations = objectCollection.locations;

	if (InputHelper::IsKeyDown(DIK_HOME))
		gameplayScene.NextStage(Map::COURTYARD);
	else if (InputHelper::IsKeyDown(DIK_1))
		player->SetPosition(locations["Checkpoint"]);
	else if (InputHelper::IsKeyDown(DIK_2))
		player->SetPosition(locations["Checkpoint_02"]);
	else if (InputHelper::IsKeyDown(DIK_3))
		player->SetPosition(locations["Checkpoint_03"]);
	else if (InputHelper::IsKeyDown(DIK_4))
		player->SetPosition(locations["Checkpoint_04"]);
	else if (InputHelper::IsKeyDown(DIK_5))
		player->SetPosition(locations["Checkpoint_05"]);
	else if (InputHelper::IsKeyDown(DIK_6))
		player->SetPosition(locations["Checkpoint_06"]);

	if (!camera->GetBounds().Intersects(player->GetFrameRect())) // player outside of viewport, update viewport postiion
	{
		camera->LookAt(player->GetPosition());
	}
}
