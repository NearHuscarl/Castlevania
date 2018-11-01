#include "GameplayScene.h"
#include "SceneManager.h"

using namespace Castlevania;

GameplayScene::GameplayScene(SceneManager &sceneManager) : AbstractScene{ sceneManager }
{
}

void GameplayScene::LoadContent()
{
}

void GameplayScene::Update(float deltaTime)
{
}

void GameplayScene::Draw(GameTime gameTime)
{
	auto spriteBatch = sceneManager.GetSpriteBatch();

	spriteBatch.GetSpriteHandler()->Begin(D3DXSPRITE_ALPHABLEND);

	// Draw stuff

	spriteBatch.GetSpriteHandler()->End();
}
