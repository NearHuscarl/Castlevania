#include <sstream>
#include "Direct2DGame/Input/InputHelper.h"
#include "MenuScene.h"
#include "SceneManager.h"

using namespace Castlevania;

constexpr auto TRANSITION_TIME = 800;

enum class MenuScene::State
{
	NORMAL,
	CHANGING_TO_NEXT_SCENE,
};

MenuScene::MenuScene(SceneManager &sceneManager) : AbstractScene{ sceneManager }
{
	startGameText = "PUSH START KEY";

	auto sstream = std::stringstream{};
	sstream
		<< "     TM AND © 1987\n"
		<< "KONAMI INDUSTRY CO.,LTD.\n"
		<< "       LICENSED BY\n"
		<< "NINTENDO OF AMERICA INC.";

	copyrightText = sstream.str();

	menuBatPosition = Vector2{ 367, 191 };
}

void MenuScene::LoadContent()
{
	auto &content = sceneManager.GetContent();
	background = content.Load<Texture>("Backgrounds/Main_Menu.png");
	menuFont = content.Load<SpriteFont>("Fonts/MainFont.font.xml");

	auto animationFactory = content.Load<AnimationFactory>("Backgrounds/Menu_Bat.ani.xml");
	menuBatSprite = std::make_unique<AnimatedSprite>(animationFactory);
	menuBatSprite->Play("fly_out");

	auto viewport = sceneManager.GetGraphicsDevice().GetViewport();
	auto startGameTextSize = menuFont->MessureString(startGameText);
	
	startGameTextPosition.x = (viewport.width - startGameTextSize.x) / 2;
	startGameTextPosition.y = (viewport.height - startGameTextSize.y) / 2 + 35;

	copyrightTextPosition.x = startGameTextPosition.x - 80;
	copyrightTextPosition.y = startGameTextPosition.y + 60;
}

void MenuScene::Update(GameTime gameTime)
{
	switch (currentState)
	{
		case State::NORMAL:
			if (InputHelper::IsKeyDown(DIK_RETURN) || InputHelper::IsKeyDown(DIK_SPACE))
			{
				transitionTimer.Start();
				currentState = State::CHANGING_TO_NEXT_SCENE;
			}

			if (menuBatSprite->AnimateComplete())
				menuBatSprite->Play("hover");

			menuBatSprite->Update();
			break;

		case State::CHANGING_TO_NEXT_SCENE:
			if (transitionTimer.ElapsedMilliseconds() >= TRANSITION_TIME)
				sceneManager.SetNextScene(Scene::GAMEPLAY);
			break;
	}
}

void MenuScene::Draw(GameTime gameTime)
{
	auto &spriteBatch = sceneManager.GetSpriteBatch();

	spriteBatch.Begin(D3DXSPRITE_ALPHABLEND);

	spriteBatch.Draw(*background, Vector2::Zero(), Color::White(), false);
	spriteBatch.DrawString(*menuFont, copyrightText, copyrightTextPosition, Color::White(), false);
	spriteBatch.Draw(*menuBatSprite, menuBatPosition, false);

	switch (currentState)
	{
		case State::NORMAL:
			spriteBatch.DrawString(*menuFont, startGameText, startGameTextPosition, Color::White());
			break;

		case State::CHANGING_TO_NEXT_SCENE:
			spriteBatch.DrawString(*menuFont, startGameText, startGameTextPosition,
				Stopwatch::Every(120) ? Color::White() : Color::Transparent());
			break;
	}

	spriteBatch.End();
}