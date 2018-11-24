#include "Direct2DGame/Input/InputHelper.h"
#include "PlaygroundScene.h"
#include "SceneManager.h"

using namespace Castlevania;

PlaygroundScene::PlaygroundScene(SceneManager &sceneManager, ObjectFactory &objectFactory) :
	AbstractScene{ sceneManager },
	objectFactory{ objectFactory }
{
	auto &graphicsDevice = sceneManager.GetGraphicsDevice();
	
	camera = std::make_unique<Camera>(sceneManager.GetGraphicsDevice());
	hud = std::make_unique<Hud>(graphicsDevice);

	stageManager = std::make_unique<StageManager>(objectFactory);
	stageManager->SetWorldPosition(Vector2{ 0, (float)hud->GetHeight() });

	player = objectFactory.CreatePlayer();
}

void PlaygroundScene::LoadContent()
{
	auto &content = sceneManager.GetContent();

	stageManager->LoadContent(content);
	hud->LoadContent(content);
	hud->Register(player->GetData());

	map = stageManager->NextMap(Map::PLAYGROUND);
	camera->SetMoveArea(0, 0, map->GetWidthInPixels(), map->GetHeightInPixels());

	objectCollection = stageManager->LoadGameObjects();

	player->SetPosition(objectCollection.locations["Checkpoint_01"]);
}

void PlaygroundScene::Update(float deltaTime)
{
	camera->LookAt(player->GetOriginPosition(), Scrolling::Horizontally);

	player->Update(deltaTime, &objectCollection);

	if (InputHelper::IsKeyDown(DIK_1))
		player->SetPosition(objectCollection.locations["Checkpoint_01"]);
	else if (InputHelper::IsKeyDown(DIK_2))
		player->SetPosition(objectCollection.locations["Checkpoint_02"]);
	else if (InputHelper::IsKeyDown(DIK_3))
		player->SetPosition(objectCollection.locations["Checkpoint_03"]);
	else if (InputHelper::IsKeyDown(DIK_4))
		objectCollection.entities.push_back(objectFactory.CreateWhipPowerup(Vector2{110, 150}));

	auto &entities = objectCollection.entities;
	for (auto const &entity : entities)
	{
		entity->Update(deltaTime, &objectCollection);
	}

	for (int i = entities.size() - 1; i >= 0; i--) // Remove dead objects
	{
		auto &entity = entities[i];

		if (entity->IsDestroyed())
			entities.erase(entities.begin() + i);
	}
}

void PlaygroundScene::Draw(GameTime gameTime)
{
	auto &spriteBatch = sceneManager.GetSpriteBatch();

	spriteBatch.Begin(D3DXSPRITE_ALPHABLEND);

	map->Draw(spriteBatch);
	hud->Draw(spriteBatch);

	for (auto const &gameObject : objectCollection.entities)
	{
		gameObject->DrawBoundingBox(spriteBatch);
		gameObject->Draw(spriteBatch);
	}

	//for (auto const &gameObject : objectCollection.boundaries)
	//{
	//	gameObject->DrawBoundingBox(spriteBatch);
	//}

	player->DrawBoundingBox(spriteBatch);
	player->Draw(spriteBatch);

	spriteBatch.End();
}
