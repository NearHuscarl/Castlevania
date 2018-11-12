#include "Controller.h"
#include "../../Settings/Button.h"

using namespace Castlevania;

Controller::Controller(Simon &player) :
	player{ player },
	keyboardState{ nullptr }
{
}

void Controller::OnKeyStateChanged(KeyboardState &keyboardState)
{
	this->keyboardState = keyboardState;

	switch (player.GetState())
	{
		case MoveState::IDLE:
			if (keyboardState.IsKeyDown(Button::WalkLeft) && keyboardState.IsKeyDown(Button::WalkRight))
				break;
			else if (keyboardState.IsKeyDown(Button::WalkLeft))
				player.WalkLeft();
			else if (keyboardState.IsKeyDown(Button::WalkRight))
				player.WalkRight();
			break;
	}
}

void Controller::OnKeyDown(int keyCode)
{
	switch (player.GetState())
	{
		case MoveState::IDLE:
			if (keyCode == Button::WalkLeft)
				player.WalkLeft();
			else if (keyCode == Button::WalkRight)
				player.WalkRight();
			else if (keyCode == Button::Jump)
				player.Jump();
			else if (keyCode == Button::Duck)
				player.Duck();
			else if (keyCode == Button::Attack)
				player.Attack();
			break;

		case MoveState::WALKING_LEFT:
		case MoveState::WALKING_RIGHT:
			if (keyboardState.IsKeyDown(Button::WalkLeft) && keyboardState.IsKeyDown(Button::WalkRight))
				player.Idle();
			else if (keyCode == Button::Jump)
				player.Jump();
			else if (keyCode == Button::Duck)
				player.Duck();
			else if (keyCode == Button::Attack)
				player.Attack();
			break;

		case MoveState::JUMPED:
		case MoveState::DUCKING:
			if (keyCode == Button::Attack)
				player.Attack();
			break;
	}
}

void Controller::OnKeyUp(int keyCode)
{
	switch (player.GetState())
	{
		case MoveState::WALKING_LEFT:
			if (keyCode == Button::WalkLeft)
				player.Idle();
			break;

		case MoveState::WALKING_RIGHT:
			if (keyCode == Button::WalkRight)
				player.Idle();
			break;

		case MoveState::DUCKING:
			if (keyCode == Button::Duck)
				player.Idle();
	}
}