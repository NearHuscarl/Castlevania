#include "Direct2DGame/Utilities/TimeHelper.h"
#include "MenuScene.h"
#include "SceneManager.h"
#include "../Settings/Fonts.h"
#include "../Settings/Audios.h"
#include "../Utilities/AudioManager.h"

using namespace Castlevania;

MenuScene::MenuScene(SceneManager &sceneManager) : AbstractScene(sceneManager)
{
}

void MenuScene::LoadContent()
{
	menuBackground = sceneManager.GetContent().Load<Texture>("Textures/Background/Main_Menu.png");

	auto viewport = sceneManager.GetGraphicsDevice().GetViewport();
	startGameTextPosition.x = (viewport.Width - Fonts::Main.MessureString(startGameText).x) / 2;
	startGameTextPosition.y = (viewport.Height - Fonts::Main.MessureString(startGameText).y) / 2 + 35;

	AudioManager::Play(GAME_START_PROLOGUE);
}

void MenuScene::Update(float deltaTime)
{
}

void MenuScene::Draw(GameTime gameTime)
{
	auto spriteBatch = sceneManager.GetSpriteBatch();

	spriteBatch.GetSpriteHandler()->Begin(D3DXSPRITE_ALPHABLEND);

	spriteBatch.Draw(*menuBackground, Vector2::Zero(), nullptr, Color::White());
	spriteBatch.DrawString(Fonts::Main, startGameText, startGameTextPosition,
		TimeHelper::Every(200) ? Color::White() : Color::Transparent());

	spriteBatch.GetSpriteHandler()->End();
}