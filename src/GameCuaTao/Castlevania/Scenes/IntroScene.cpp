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
}

void IntroScene::LoadContent()
{
	auto viewport = sceneManager.GetGraphicsDevice().GetViewport();

	background = sceneManager.GetContent().Load<Texture>("Textures/Background/Intro_Scene.png");
	
	simon->LoadContent(sceneManager.GetContent());
	
	startPosition = Vector2{ (float)viewport.width - simon->GetBoundingBox().Width() / 2, GROUND_POSITION_Y };
	gatePosition = Vector2{ (float)viewport.width / 2, GROUND_POSITION_Y };

	simon->SetPosition(startPosition);
	
	AudioManager::Play(GAME_START_PROLOGUE);
}

void IntroScene::Update(float deltaTime)
{
	if (simon->GetOriginPosition().x >= gatePosition.x)
		simon->WalkLeft();
	else
		simon->TurnBackward();

	simon->Update(deltaTime);
}

void IntroScene::Draw(GameTime gameTime)
{
	auto spriteBatch = sceneManager.GetSpriteBatch();

	spriteBatch.GetSpriteHandler()->Begin(D3DXSPRITE_ALPHABLEND);

	spriteBatch.Draw(*background, Vector2::Zero(), nullptr, Color::White());
	simon->Draw(spriteBatch);

	spriteBatch.GetSpriteHandler()->End();
}
