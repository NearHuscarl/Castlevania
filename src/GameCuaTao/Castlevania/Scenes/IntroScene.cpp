#include "Direct2DGame/Base/Vector2.h"
#include "IntroScene.h"
#include "SceneManager.h"
#include "../Settings/Audios.h"
#include "../Utilities/AudioManager.h"

using namespace Castlevania;

constexpr auto GROUND_POSITION_Y = 338.f;

IntroScene::IntroScene(SceneManager &sceneManager) : AbstractScene{ sceneManager }
{
	simon = std::make_unique<Simon>();
	bat1 = std::make_unique<Bat>();
	bat2 = std::make_unique<Bat>();
}

void IntroScene::LoadContent()
{
	auto viewport = sceneManager.GetGraphicsDevice().GetViewport();

	background = sceneManager.GetContent().Load<Texture>("Textures/Background/Intro_Scene.png");
	
	simon->LoadContent(sceneManager.GetContent());
	bat1->LoadContent(sceneManager.GetContent());
	bat2->LoadContent(sceneManager.GetContent());

	startPosition = Vector2{ (float)viewport.width - simon->GetBoundingBox().Width() / 2, GROUND_POSITION_Y };
	gatePosition = Vector2{ (float)viewport.width / 2, GROUND_POSITION_Y };

	simon->SetPosition(startPosition);

	bat1->SetPosition(288, 115);
	bat2->SetPosition(41, 232);

	AudioManager::Play(GAME_START_PROLOGUE);
}

void IntroScene::Update(float deltaTime)
{
	if (simon->GetOriginPosition().x >= gatePosition.x)
		simon->WalkLeft();
	else
		simon->TurnBackward();

	bat1->Update(deltaTime);
	bat2->Update(deltaTime);

	simon->Update(deltaTime);
}

void IntroScene::Draw(GameTime gameTime)
{
	auto spriteBatch = sceneManager.GetSpriteBatch();

	spriteBatch.GetSpriteHandler()->Begin(D3DXSPRITE_ALPHABLEND);

	spriteBatch.Draw(*background, Vector2::Zero(), nullptr, Color::White());
	simon->Draw(spriteBatch);
	bat1->Draw(spriteBatch);
	bat2->Draw(spriteBatch);

	spriteBatch.GetSpriteHandler()->End();
}
