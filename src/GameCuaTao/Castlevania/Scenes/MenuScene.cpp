#include "Direct2DGame/Input/InputHelper.h"
#include "MenuScene.h"
#include "SceneManager.h"
#include "../Settings/Fonts.h"

using namespace Castlevania;

MenuScene::MenuScene(SceneManager &sceneManager) : AbstractScene{ sceneManager }
{
}

void MenuScene::LoadContent()
{
	background = sceneManager.GetContent().Load<Texture>("Textures/Backgrounds/Main_Menu.png");

	auto viewport = sceneManager.GetGraphicsDevice().GetViewport();
	auto startGameTextSize = Fonts::Main.MessureString(startGameText);
	
	startGameTextPosition.x = (viewport.width - startGameTextSize.x) / 2;
	startGameTextPosition.y = (viewport.height - startGameTextSize.y) / 2 + 35;
}

void MenuScene::Update(float deltaTime)
{
	if (InputHelper::IsKeyPressed(DIK_RETURN))
	{
		transitionTimer.Start();
	}
	else if (InputHelper::IsKeyPressed(DIK_HOME))
	{
		sceneManager.SetNextScene(Scene::GAMEPLAY);
	}

	if (transitionTimer.ElapsedMilliseconds() >= 800)
	{
		sceneManager.SetNextScene(Scene::INTRO);
	}
}

void MenuScene::Draw(GameTime gameTime)
{
	auto &spriteBatch = sceneManager.GetSpriteBatch();

	spriteBatch.Begin(D3DXSPRITE_ALPHABLEND);

	spriteBatch.Draw(*background, Vector2::Zero(), Color::White());

	if (!transitionTimer.IsRunning())
	{
		spriteBatch.DrawString(Fonts::Main, startGameText, startGameTextPosition, Color::White());
	}
	else
	{
		spriteBatch.DrawString(Fonts::Main, startGameText, startGameTextPosition,
			Stopwatch::Every(120) ? Color::White() : Color::Transparent());
	}

	spriteBatch.End();
}