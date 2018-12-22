#include "Direct2DGame/Base/Vector2.h"
#include "IntroScene.h"
#include "SceneManager.h"
#include "../Models/UpdateData.h"
#include "../Settings/Audios.h"
#include "../Utilities/AudioManager.h"

using namespace Castlevania;

constexpr auto GROUND_POSITION_Y = 338.f;

IntroScene::IntroScene(SceneManager &sceneManager) : AbstractScene{ sceneManager }
{
	auto &objectFactory = sceneManager.GetFactory();

	player = objectFactory.CreateIntroSimon();
	bat1 = objectFactory.CreateBat();
	bat2 = objectFactory.CreateBat();
}

void IntroScene::LoadContent()
{
	auto viewport = sceneManager.GetGraphicsDevice().GetViewport();

	background = sceneManager.GetContent().Load<Texture>("Backgrounds/Intro_Scene.png");
	
	startPosition = Vector2{ (float)viewport.width - player->GetBoundingBox().Width() / 2, GROUND_POSITION_Y };
	gatePosition = Vector2{ (float)viewport.width / 2, GROUND_POSITION_Y };

	player->SetPosition(startPosition);

	bat1->SetPosition(41, 210);
	bat1->SetSpeed(40);
	bat1->SetDirection(30);

	bat2->SetPosition(288, 115);
	bat1->SetSpeed(12);
	bat2->SetDirection(165);

	AudioManager::Play(GAME_START_PROLOGUE);
}

void IntroScene::Update(GameTime gameTime)
{
	if (player->GetOriginPosition().x >= gatePosition.x)
	{
		player->WalkLeft();
	}
	else
	{
		player->TurnBackward();
		transitionTimer.Start();
	}

	if (transitionTimer.ElapsedMilliseconds() > 4000)
	{
		sceneManager.SetNextScene(Scene::GAMEPLAY);
	}

	bat1->Update(UpdateData{ gameTime });
	bat2->Update(UpdateData{ gameTime });

	player->Update(UpdateData{ gameTime });
}

void IntroScene::Draw(GameTime gameTime)
{
	auto &spriteBatch = sceneManager.GetSpriteBatch();

	spriteBatch.Begin(D3DXSPRITE_ALPHABLEND);

	spriteBatch.Draw(*background, Vector2::Zero(), Color::White());
	player->Draw(spriteBatch);
	bat1->Draw(spriteBatch);
	bat2->Draw(spriteBatch);

	spriteBatch.End();
}
