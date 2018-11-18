#include "Controller.h"
#include "../../../Settings/Button.h"

using namespace Castlevania;

Controller::Controller(Player &player) :
	player{ player },
	keyboardState{ nullptr }
{
}

void Controller::OnKeyStateChanged(KeyboardState &keyboardState)
{
	this->keyboardState = keyboardState;

	if (player.GetAttackState() == AttackState::ATTACKING)
		return;

	switch (player.GetMoveState())
	{
		case MoveState::IDLE:
			if (keyboardState.IsKeyDown(Button::WalkLeft) && keyboardState.IsKeyDown(Button::WalkRight))
				break;
			else if (keyboardState.IsKeyDown(Button::WalkLeft))
				player.WalkLeft();
			else if (keyboardState.IsKeyDown(Button::WalkRight))
				player.WalkRight();
			else if (keyboardState.IsKeyDown(Button::Duck))
				player.Duck();
			break;

		case MoveState::WALKING:
			if (keyboardState.IsKeyUp(Button::WalkLeft) && player.GetFacing() == Facing::Left
				|| keyboardState.IsKeyUp(Button::WalkRight) && player.GetFacing() == Facing::Right)
				player.Idle();
			break;

		case MoveState::DUCKING:
			if (keyboardState.IsKeyUp(Button::Duck))
				player.Idle();
			break;
	}
}

void Controller::OnKeyDown(int keyCode)
{
	if (player.GetAttackState() == AttackState::ATTACKING)
		return;

	switch (player.GetMoveState())
	{
		case MoveState::IDLE:
			if (keyCode == Button::Jump)
				player.Jump();
			else if (keyCode == Button::Attack)
				player.Attack();
			break;

		case MoveState::WALKING:
			if (keyboardState.IsKeyDown(Button::WalkLeft) && keyboardState.IsKeyDown(Button::WalkRight))
				player.Idle();
			else if (keyCode == Button::Jump)
				player.Jump();
			else if (keyCode == Button::Duck)
				player.Duck();
			else if (keyCode == Button::Attack)
				player.Attack();
			break;

		case MoveState::JUMPING:
		case MoveState::FALLING:
		case MoveState::LANDING:
		case MoveState::DUCKING:
			if (keyCode == Button::Attack)
				player.Attack();
			break;
	}
}

void Controller::OnKeyUp(int keyCode)
{
	if (player.GetAttackState() == AttackState::ATTACKING)
		return;
}