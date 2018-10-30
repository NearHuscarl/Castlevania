#include "Player.h"
#include "Direct2DGame/Input/InputHelper.h"

using namespace Castlevania;

void Player::Update(float deltaTime)
{
	UpdateInput();

	Simon::Update(deltaTime);
}

void Player::UpdateInput()
{
	//switch (state)
	//{
	//	case IDLE:
	//		break;
	//}
	if (InputHelper::IsKeyDown(DIK_RIGHT))
	{
		WalkRight();
	}
	else if (InputHelper::IsKeyDown(DIK_LEFT))
	{
		WalkLeft();
	}
}
