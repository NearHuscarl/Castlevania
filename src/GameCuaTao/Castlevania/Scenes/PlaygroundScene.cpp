#include "Direct2DGame/Input/InputHelper.h"
#include "PlaygroundScene.h"
#include "SceneManager.h"
#include "../Utilities/SpriteHelper.h"

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
		player->SetPosition(objectCollection.locations["Checkpoint_04"]);
	else if (InputHelper::IsKeyDown(DIK_W))
		objectCollection.entities.push_back(objectFactory.CreateWhipPowerup(Vector2{ 110, 150 }));

	auto &entities = objectCollection.entities;
	auto sizeThisTurn = entities.size();

	for (unsigned int i = 0; i < sizeThisTurn; i++)
	{
		entities[i]->Update(deltaTime, &objectCollection);
	}

	objectCollection.RemoveDeadObjects();
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

	for (auto const &trigger : objectCollection.triggers)
	{
		SpriteHelper::DrawRectangle(spriteBatch, trigger->GetBoundingBox(), Color::Blue() * 0.75f);
	}

	player->DrawBoundingBox(spriteBatch);
	player->Draw(spriteBatch);

	spriteBatch.End();
}
