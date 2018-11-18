#include "PlaygroundScene.h"
#include "SceneManager.h"

using namespace Castlevania;

PlaygroundScene::PlaygroundScene(SceneManager &sceneManager) : AbstractScene{ sceneManager }
{
	camera = std::make_unique<Camera>(sceneManager.GetGraphicsDevice());
	stageManager = std::make_unique<StageManager>();
}

void PlaygroundScene::LoadContent()
{
	auto &content = sceneManager.GetContent();

	stageManager->LoadContent(content);
	map = stageManager->NextMap(Map::PLAYGROUND);
	camera->SetMoveArea(0, 0, map->GetWidthInPixels(), map->GetHeightInPixels());

	objectCollection = stageManager->LoadGameObjects();

	player = objectFactory.CreatePlayer();
	player->SetPosition(objectCollection.locations[CHECKPOINT]);
	player->LoadContent(content);

	for (auto &entity : objectCollection.entities) // TODO: put LoadContent in constructor?
	{
		entity->LoadContent(content);
	}
}

void PlaygroundScene::Update(float deltaTime)
{
	camera->LookAt(player->GetOriginPosition(), Scrolling::Horizontally);

	player->Update(deltaTime, &objectCollection);

	for (auto const &gameObject : objectCollection.entities)
	{
		gameObject->Update(deltaTime);
	}
}

void PlaygroundScene::Draw(GameTime gameTime)
{
	auto &spriteBatch = sceneManager.GetSpriteBatch();

	spriteBatch.Begin(D3DXSPRITE_ALPHABLEND);

	map->Draw(spriteBatch);

	for (auto const &gameObject : objectCollection.entities)
	{
		gameObject->DrawBoundingBox(spriteBatch);
		gameObject->Draw(spriteBatch);
	}

	for (auto const &gameObject : objectCollection.boundaries)
	{
		gameObject->DrawBoundingBox(spriteBatch);
	}

	player->DrawBoundingBox(spriteBatch);
	player->Draw(spriteBatch);

	spriteBatch.End();
}
