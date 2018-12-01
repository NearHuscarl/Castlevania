#include "Direct2DGame/Input/InputHelper.h"
#include "PlaygroundStage.h"
#include "../GameplayScene.h"

using namespace Castlevania;

PlaygroundStage::PlaygroundStage(GameplayScene &gameplayScene) : Stage{ gameplayScene, Map::PLAYGROUND }
{
}

void PlaygroundStage::Update(GameTime gameTime)
{
	UpdateInput();
	UpdateGameplay(gameTime);
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
	else if (InputHelper::IsKeyDown(DIK_NUMPAD1))
	{
		auto object = objectFactory.CreateZombie(locations["Checkpoint_05"]);
		object->WalkRight();
		objectCollection.entities.push_back(std::move(object));
	}
	else if (InputHelper::IsKeyDown(DIK_W))
	{
		auto playerLocation = player->GetPosition();
		auto spawnLocation = Vector2{ playerLocation.x + 60, playerLocation.y - 100 };
		objectCollection.entities.push_back(objectFactory.CreateWhipPowerup(spawnLocation));
	}

	if (!camera->GetBounds().Intersects(player->GetFrameRect())) // player outside of viewport, update viewport postiion
	{
		camera->LookAt(player->GetPosition());
	}
}
