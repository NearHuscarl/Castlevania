#include "Controller.h"
#include "../../../Settings/Button.h"

using namespace Castlevania;

Controller::Controller(Player &player, ObjectFactory &objectFactory) :
	player{ player },
	keyboardState{ nullptr },
	objectFactory{ objectFactory }
{
}

void Controller::OnKeyStateChanged(KeyboardState &keyboardState)
{
	this->keyboardState = keyboardState;
}

void Controller::OnKeyDown(int keyCode)
{
	auto attackState = player.GetAttackState();

	if (attackState == AttackState::WHIPPING ||
		attackState == AttackState::THROWING)
		return;

	switch (player.GetMoveState())
	{
		case MoveState::IDLE:
			if (keyCode == Button::Jump)
				player.Jump();
			else if (keyCode == Button::Attack)
				player.Attack();
			else if (keyCode == Button::Throw)
				Throw();
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
			else if (keyCode == Button::Throw)
				Throw();
			break;

		case MoveState::JUMPING:
		case MoveState::FALLING:
		case MoveState::LANDING:
		case MoveState::DUCKING:
			if (keyCode == Button::Attack)
				player.Attack();
			else if (keyCode == Button::Throw)
				Throw();
			break;
	}
}

void Controller::OnKeyUp(int keyCode)
{
	auto attackState = player.GetAttackState();

	if (attackState == AttackState::WHIPPING ||
		attackState == AttackState::THROWING)
		return;
}

void Controller::Update()
{
	auto attackState = player.GetAttackState();

	if (attackState == AttackState::WHIPPING ||
		attackState == AttackState::THROWING)
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

void Controller::Throw()
{
	auto weaponItem = player.GetSecondaryWeapon();

	switch (weaponItem)
	{
		case EntityType::KnifeItem:
		{
			auto weapon = objectFactory.CreateKnife(); // TODO: put this into object collection
			
			player.Throw(std::move(weapon));
			break;
		}
	}
}
