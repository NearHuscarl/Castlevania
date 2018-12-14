#include "GameplayScene.h"
#include "SceneManager.h"

using namespace Castlevania;

GameplayScene::GameplayScene(SceneManager &sceneManager) : AbstractScene{ sceneManager }
{
	auto &objectFactory = sceneManager.GetFactory();
	auto &graphicsDevice = sceneManager.GetGraphicsDevice();

	mapManager = std::make_unique<MapManager>(objectFactory);
	player = std::move(objectFactory.CreatePlayer());

	data = std::make_unique<GameplayData>();

	hud = std::make_shared<Hud>(graphicsDevice);
	hud->Register(player->GetData());
	hud->Register(*data);
}

SceneManager &GameplayScene::GetSceneManager()
{
	return sceneManager;
}

MapManager &GameplayScene::GetMapManager()
{
	return *mapManager;
}

std::shared_ptr<Player> GameplayScene::GetPlayer()
{
	return player;
}

std::shared_ptr<Hud> GameplayScene::GetHud()
{
	return hud;
}

std::shared_ptr<GameplayData> GameplayScene::GetData()
{
	return data;
}

void GameplayScene::NextStage(Map map, std::string spawnPoint)
{
	nextStage = std::make_unique<Stage>(*this, map, spawnPoint);
}

void GameplayScene::LoadContent()
{
	auto &content = sceneManager.GetContent();

	mapManager->LoadContent(content);
	hud->LoadContent(content);

	NextStage(Map::COURTYARD); // TODO: change back to COURTYARD
}

void GameplayScene::Update(GameTime gameTime)
{
	if (nextStage != nullptr)
	{
		currentStage = std::move(nextStage);
		currentStage->Initialize();
	}

	currentStage->Update(gameTime);
}

void GameplayScene::Draw(GameTime gameTime)
{
	auto &spriteBatch = sceneManager.GetSpriteBatch();
	
	spriteBatch.Begin(D3DXSPRITE_ALPHABLEND);
	currentStage->Draw(spriteBatch);
	spriteBatch.End();
}
