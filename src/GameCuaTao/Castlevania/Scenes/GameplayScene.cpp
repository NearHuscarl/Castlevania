#include "GameplayScene.h"
#include "SceneManager.h"

using namespace Castlevania;

GameplayScene::GameplayScene(SceneManager &sceneManager) : AbstractScene{ sceneManager }
{
	camera = std::make_unique<Camera>(sceneManager.GetGraphicsDevice());
}

void GameplayScene::LoadContent()
{
	auto &stageManager = sceneManager.GetStageManager();
	
	map = stageManager.NextMap(Map::STAGE_01_COURTYARD);
	gameObjects = stageManager.LoadGameObjects();
	camera->SetMoveArea(0, 0, map->GetWidthInPixels(), map->GetHeightInPixels());

	for (auto &gameObject : gameObjects)
	{
		gameObject->LoadContent(sceneManager.GetContent());

		if (gameObject->GetType() == EntityType::Player)
		{
			player = dynamic_cast<Player*>(gameObject.get());
		}
	}
}

void GameplayScene::Update(float deltaTime)
{
	camera->LookAt(player->GetOriginPosition(), Scrolling::Horizontally);

	for (auto const &gameObject : gameObjects)
	{
		gameObject->Update(deltaTime);
	}
}

void GameplayScene::Draw(GameTime gameTime)
{
	auto &spriteBatch = sceneManager.GetSpriteBatch();

	spriteBatch.Begin(D3DXSPRITE_ALPHABLEND);

	map->Draw(spriteBatch);

	for (auto const &gameObject : gameObjects)
	{
		gameObject->Draw(spriteBatch);
	}

	spriteBatch.End();
}
