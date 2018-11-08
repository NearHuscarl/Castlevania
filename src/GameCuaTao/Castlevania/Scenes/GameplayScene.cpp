#include "GameplayScene.h"
#include "SceneManager.h"
#include "Direct2DGame/Extensions/Tiled/TiledMap.h"

using namespace Castlevania;

GameplayScene::GameplayScene(SceneManager &sceneManager) : AbstractScene{ sceneManager }
{
	auto tiledMap = sceneManager.GetContent().Load<TiledMap>("TiledMaps/Intro.tmx");
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
