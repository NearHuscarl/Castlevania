#include "MarioController.h"
#include "Mario.h"

using namespace MarioSample;

MarioController::MarioController(Mario &player) : player{ player }
{
}

void MarioController::OnKeyStateChanged(KeyboardState &keyboardState)
{
	switch (player.GetState())
	{
		case State::IDLE:
			if (keyboardState.IsKeyDown(DIK_SPACE))
				player.Jump();
			if (keyboardState.IsKeyDown(DIK_RIGHT))
				player.WalkRight();
			else if (keyboardState.IsKeyDown(DIK_LEFT))
				player.WalkLeft();
			break;
	}
}

void MarioController::OnKeyDown(int keyCode)
{
	switch (player.GetState())
	{
		case State::IDLE:
		case State::WALKING_LEFT:
		case State::WALKING_RIGHT:
			if (keyCode == DIK_SPACE)
				player.Jump();
			break;
	}
}

void MarioController::OnKeyUp(int keyCode)
{
	switch (player.GetState())
	{
		case State::WALKING_LEFT:
			if (keyCode == DIK_LEFT)
				player.Idle();
			break;

		case State::WALKING_RIGHT:
			if (keyCode == DIK_RIGHT)
				player.Idle();
			break;
	}
}