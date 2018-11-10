#include "Player.h"
#include "Direct2DGame/Input/InputHelper.h"

using namespace Castlevania;

Player::Player() : Simon(EntityType::Player)
{
}

void Player::Update(float deltaTime)
{
	UpdateInput();

	Simon::Update(deltaTime);
}

void Player::UpdateInput()
{
	if (InputHelper::IsKeyPressed(DIK_RIGHT))
		WalkRight();
	else if (InputHelper::IsKeyPressed(DIK_LEFT))
		WalkLeft();
	else
		Idle();
}
