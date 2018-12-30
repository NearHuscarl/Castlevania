#include <sstream>
#include "Direct2DGame/Input/InputHelper.h"
#include "GameOverScene.h"
#include "SceneManager.h"
#include "GameplayScene.h"

using namespace Castlevania;

constexpr auto GAME_OVER_TEXT = "GAME OVER";
constexpr auto CONTINUE_TEXT = "CONTINUE";
constexpr auto END_TEXT = "END";

GameOverScene::GameOverScene(SceneManager &sceneManager) : AbstractScene{ sceneManager }
{
	currentOption = CONTINUE_TEXT;
}

void GameOverScene::LoadContent()
{
	auto &content = sceneManager.GetContent();
	
	font = content.Load<SpriteFont>("Fonts/MainFont.font.xml");
	heartTexture = content.Load<Texture>("Hud/Heart.png");

	auto viewport = sceneManager.GetGraphicsDevice().GetViewport();
	auto gameOverTextSize = font->MessureString(GAME_OVER_TEXT);

	gameOverTextPosition.x = (viewport.width - gameOverTextSize.x) / 2;
	gameOverTextPosition.y = (viewport.height - gameOverTextSize.y) / 2;

	continueTextPosition.x = gameOverTextPosition.x + 12;
	continueTextPosition.y = gameOverTextPosition.y + 80;

	endTextPosition.x = gameOverTextPosition.x + 12;
	endTextPosition.y = gameOverTextPosition.y + 130;
}

void GameOverScene::Update(GameTime gameTime)
{
	if (InputHelper::IsKeyDown(DIK_DOWN) || InputHelper::IsKeyDown(DIK_UP))
	{
		if (currentOption == CONTINUE_TEXT)
			currentOption = END_TEXT;
		else
			currentOption = CONTINUE_TEXT;
	}

	if (InputHelper::IsKeyDown(DIK_RETURN))
	{
		if (currentOption == CONTINUE_TEXT)
		{
			sceneManager.SetNextScene(Scene::GAMEPLAY);
			dynamic_cast<GameplayScene&>(sceneManager.GetNextScene()).NextStage(Map::COURTYARD);
		}
		else
			sceneManager.SetNextScene(Scene::MENU);
	}
}

void GameOverScene::Draw(GameTime gameTime)
{
	auto &spriteBatch = sceneManager.GetSpriteBatch();

	spriteBatch.Begin(D3DXSPRITE_ALPHABLEND);

	spriteBatch.Draw(*heartTexture, GetHeartPosition(), Color::White());
	spriteBatch.DrawString(*font, GAME_OVER_TEXT, gameOverTextPosition, Color::White());
	spriteBatch.DrawString(*font, CONTINUE_TEXT, continueTextPosition, Color::White());
	spriteBatch.DrawString(*font, END_TEXT, endTextPosition, Color::White());

	spriteBatch.End();
}

Vector2 GameOverScene::GetHeartPosition()
{
	if (currentOption == CONTINUE_TEXT)
		return Vector2{ continueTextPosition.x - 30, continueTextPosition.y };
	else
		return Vector2{ endTextPosition.x - 30, endTextPosition.y };
}
