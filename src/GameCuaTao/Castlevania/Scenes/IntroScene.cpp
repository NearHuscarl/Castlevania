#include "Direct2DGame/Base/Vector2.h"
#include "IntroScene.h"
#include "SceneManager.h"
#include "../Settings/Audios.h"
#include "../Utilities/AudioManager.h"

using namespace Castlevania;

constexpr auto GROUND_POSITION_Y = 338.f;

IntroScene::IntroScene(SceneManager &sceneManager) : AbstractScene{ sceneManager }
{
	player = std::make_unique<Player>();
	bat1 = std::make_unique<Bat>();
	bat2 = std::make_unique<Bat>();
}

void IntroScene::LoadContent()
{
	auto viewport = sceneManager.GetGraphicsDevice().GetViewport();

	background = sceneManager.GetContent().Load<Texture>("Textures/Backgrounds/Intro_Scene.png");
	
	player->LoadContent(sceneManager.GetContent());
	bat1->LoadContent(sceneManager.GetContent());
	bat2->LoadContent(sceneManager.GetContent());

	startPosition = Vector2{ (float)viewport.width - player->GetBoundingBox().Width() / 2, GROUND_POSITION_Y };
	gatePosition = Vector2{ (float)viewport.width / 2, GROUND_POSITION_Y };

	player->SetPosition(startPosition);

	bat1->SetPosition(41, 210);
	bat1->SetLinearVelocity(40, 30);

	bat2->SetPosition(288, 115);
	bat2->SetLinearVelocity(12, 165);

	AudioManager::Play(GAME_START_PROLOGUE);
}

void IntroScene::Update(float deltaTime)
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

	bat1->Update(deltaTime);
	bat2->Update(deltaTime);

	player->Update(deltaTime);
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
