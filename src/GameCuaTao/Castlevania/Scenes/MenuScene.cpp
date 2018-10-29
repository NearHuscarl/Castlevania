#include "Direct2DGame/Input/InputHelper.h"
#include "MenuScene.h"
#include "SceneManager.h"
#include "../Settings/Fonts.h"

using namespace Castlevania;

MenuScene::MenuScene(SceneManager &sceneManager) : AbstractScene(sceneManager)
{
}

void MenuScene::LoadContent()
{
	background = sceneManager.GetContent().Load<Texture>("Textures/Background/Main_Menu.png");

	auto viewport = sceneManager.GetGraphicsDevice().GetViewport();
	auto startGameTextSize = Fonts::Main.MessureString(startGameText);
	
	startGameTextPosition.x = (viewport.Width - startGameTextSize.x) / 2;
	startGameTextPosition.y = (viewport.Height - startGameTextSize.y) / 2 + 35;
}

void MenuScene::Update(float deltaTime)
{
	if (InputHelper::IsKeyPressed(DIK_RETURN))
	{
		transitionTimer.Start();
	}

	if (transitionTimer.ElapsedMilliseconds() >= 800)
	{
		sceneManager.SetNextScene(Scene::INTRO);
	}
}

void MenuScene::Draw(GameTime gameTime)
{
	auto spriteBatch = sceneManager.GetSpriteBatch();

	spriteBatch.GetSpriteHandler()->Begin(D3DXSPRITE_ALPHABLEND);

	spriteBatch.Draw(*background, Vector2::Zero(), nullptr, Color::White());

	if (!transitionTimer.IsRunning())
	{
		spriteBatch.DrawString(Fonts::Main, startGameText, startGameTextPosition, Color::White());
	}
	else
	{
		spriteBatch.DrawString(Fonts::Main, startGameText, startGameTextPosition,
			Stopwatch::Every(120) ? Color::White() : Color::Transparent());
	}

	spriteBatch.GetSpriteHandler()->End();
}