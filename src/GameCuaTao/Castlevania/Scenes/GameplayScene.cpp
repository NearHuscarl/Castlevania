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
	camera->SetMoveArea(0, 0, map->GetWidthInPixels(), map->GetHeightInPixels());
	
	objectCollection = stageManager.LoadGameObjects();
	
	player = std::make_unique<Player>();
	player->SetPosition(objectCollection.positions[CHECKPOINT]);
	player->LoadContent(sceneManager.GetContent());

	Keyboard::Register(player->GetController());

	for (auto &entity : objectCollection.entities) // TODO: put LoadContent in constructor?
	{
		entity->LoadContent(sceneManager.GetContent());
	}
}

void GameplayScene::Update(float deltaTime)
{
	camera->LookAt(player->GetOriginPosition(), Scrolling::Horizontally);

	player->Update(deltaTime);

	for (auto const &gameObject : objectCollection.entities)
	{
		gameObject->Update(deltaTime);
	}
}

void GameplayScene::Draw(GameTime gameTime)
{
	auto &spriteBatch = sceneManager.GetSpriteBatch();

	spriteBatch.Begin(D3DXSPRITE_ALPHABLEND);

	map->Draw(spriteBatch);

	for (auto const &gameObject : objectCollection.entities)
	{
		gameObject->Draw(spriteBatch);
	}

	player->Draw(spriteBatch);

	spriteBatch.End();
}
