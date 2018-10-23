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

	AudioManager::Play(GAME_START_PROLOGUE);
}

void MenuScene::Update(float deltaTime)
{
}

void MenuScene::Draw(GameTime gameTime)
{
	auto spriteBatch = sceneManager.GetSpriteBatch();

	spriteBatch.GetSpriteHandler()->Begin(D3DXSPRITE_ALPHABLEND);

	spriteBatch.Draw(*menuBackground, Vector::Zero(), nullptr, Color::White());
	spriteBatch.DrawString(Fonts::Main, "PUSH START KEY", Vector(40, 40), Color::White());

	spriteBatch.GetSpriteHandler()->End();
}