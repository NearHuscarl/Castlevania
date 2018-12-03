#include "GameplayScene.h"
#include "SceneManager.h"
#include "Stages/CourtyardStage.h"
#include "Stages/GreatHallStage.h"
#include "Stages/PlaygroundStage.h"

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

Sprite &GameplayScene::GetCutsceneBackground()
{
	return *cutsceneBackground;
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

void GameplayScene::NextStage(Map map)
{
	nextStage = ConstructStage(map);
}

void GameplayScene::LoadContent()
{
	auto &content = sceneManager.GetContent();

	mapManager->LoadContent(content);
	hud->LoadContent(content);

	auto cutsceneBgTexture = content.Load<Texture>("Backgrounds/Cutscene_Background.png");
	cutsceneBackground = std::make_unique<Sprite>(cutsceneBgTexture);

	currentStage = ConstructStage(Map::COURTYARD);
	currentStage->Initialize();
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

std::unique_ptr<Stage> GameplayScene::ConstructStage(Map map)
{
	switch (map)
	{
		case Map::COURTYARD:
			return std::make_unique<CourtyardStage>(*this);

		case Map::GREAT_HALL:
			return std::make_unique<GreatHallStage>(*this);

		case Map::PLAYGROUND:
			return std::make_unique<PlaygroundStage>(*this);

		default:
			return nullptr;
	}
}
