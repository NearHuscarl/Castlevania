#include "Game.h"
#include "windows.h"
#include "DemoGame.h"

#include "Models/GameObject.h"
#include "Animation/TextureManager.h"

#include "Animation/SpriteManager.h"
#include "Animation/Animation.h"
#include "Animation/AnimationManager.h"

#include "Models/Mario.h"

// TODO: refactor
#define ID_TEX_MARIO 0

// TODO: refactor
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

DemoGame::DemoGame(HINSTANCE hInstance, int nCmdShow)
	: Game(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT)
{

}

void DemoGame::Initialize()
{
	Game::Initialize();
}

void DemoGame::LoadResources()
{
	TextureManager * textureManager = TextureManager::GetInstance();

	textureManager->Add(ID_TEX_MARIO, L"textures\\mario.png", D3DCOLOR_XRGB(176, 224, 248));

	SpriteManager *sprites = SpriteManager::GetInstance();
	AnimationManager *animations = AnimationManager::GetInstance();

	GTexturePtr texMario = textureManager->Get(ID_TEX_MARIO);


	sprites->Add(10001, 246, 154, 260, 181, texMario);

	sprites->Add(10002, 275, 154, 290, 181, texMario);
	sprites->Add(10003, 304, 154, 321, 181, texMario);

	sprites->Add(10011, 186, 154, 200, 181, texMario);

	sprites->Add(10012, 155, 154, 170, 181, texMario);
	sprites->Add(10013, 125, 154, 140, 181, texMario);


	Animation *ani;

	ani = new Animation(100);
	ani->Add(10001);
	animations->Add(400, ani);

	ani = new Animation(100);
	ani->Add(10011);
	animations->Add(401, ani);


	ani = new Animation(100);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	animations->Add(500, ani);

	ani = new Animation(100);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	animations->Add(501, ani);

	mario = new Mario();
	Mario::AddAnimation(400);		// idle right
	Mario::AddAnimation(401);		// idle left
	Mario::AddAnimation(500);		// walk right
	Mario::AddAnimation(501);		// walk left

	mario->SetPosition(0.0f, 100.0f);
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void DemoGame::Update(DWORD dt)
{
	mario->Update(dt);
}

void DemoGame::Draw()
{
	mario->Render();
}