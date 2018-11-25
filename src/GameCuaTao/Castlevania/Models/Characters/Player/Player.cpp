#include "Direct2DGame/Input/InputHelper.h"
#include "Player.h"
#include "PlayerSettings.h"

using namespace Castlevania;

constexpr auto JUMP_COOLDOWN = 400; // milliseconds

Player::Player() : GameObject(EntityType::Player)
{
	this->whip = std::make_unique<Whip>(*this);
}

void Player::SetFacing(Facing facing)
{
	GameObject::SetFacing(facing);
	whip->SetFacing(facing);
	SendMessageToSystems(FACING_CHANGED);
}

void Player::SetMoveState(MoveState moveState)
{
	this->moveState = moveState;
	SendMessageToSystems(MOVE_STATE_CHANGED);
}

void Player::SetAttackState(AttackState attackState)
{
	if (moveState == MoveState::WALKING)
		velocity.x = 0;

	this->attackState = attackState;
	SendMessageToSystems(ATTACK_STATE_CHANGED);
}

const PlayerData &Player::GetData()
{
	return data;
}

void Player::SetWhip(std::unique_ptr<Whip> whip)
{
	this->whip = std::move(whip);
}

MoveState Player::GetMoveState()
{
	return moveState;
}

AttackState Player::GetAttackState()
{
	return attackState;
}

EntityType Player::GetSecondaryWeapon()
{
	return data.secondaryWeapon;
}

void Player::SetSecondaryWeapon(EntityType weapon)
{
	//secondaryWeapon->GetBody().Enabled(false);
	data.secondaryWeapon = weapon;
}

void Player::LoadContent(ContentManager &content)
{
	GameObject::LoadContent(content);

	auto stats = content.Load<Dictionary>("CharacterStats/Simon.xml");
	speed = std::stof(stats->at("WalkSpeed"));
	jumpSpeed = std::stof(stats->at("JumpSpeed"));

	Idle();
}

void Player::Update(float deltaTime, ObjectCollection *objectCollection)
{
	if (InputHelper::IsKeyDown(DIK_9)) // NOTE: remove debugging code
		data.hearts += 20;
	else if (InputHelper::IsKeyDown(DIK_0))
		data.playerHealth = MAX_HEALTH;

	GameObject::Update(deltaTime, objectCollection);
	UpdateStates(deltaTime);

	whip->Update(deltaTime, objectCollection);

	for (auto &weapon : secondaryWeapons)
		weapon->Update(deltaTime, objectCollection);
}

void Player::UpdateStates(float deltaTime)
{
	switch (moveState)
	{
		case MoveState::JUMPING:
			if (velocity.y >= 0)
				SetMoveState(MoveState::FALLING);
			break;

		case MoveState::LANDING_HARD:
			if (landingTimer.ElapsedMilliseconds() >= JUMP_COOLDOWN)
			{
				Idle();
				landingTimer.Reset();
			}
			break;
	}

	data.timeLeft.CountDown();
}

void Player::OnAttackComplete()
{
	switch (attackState)
	{
		case AttackState::WHIPPING:
			whip->Withdraw();
			break;
	}

	switch (moveState)
	{
		case MoveState::WALKING:
		case MoveState::IDLE:
			Idle();
			break;

		case MoveState::JUMPING:
		case MoveState::FALLING:
			SetMoveState(MoveState::LANDING);
			break;

		case MoveState::DUCKING:
			Duck();
			break;
	}

	SetAttackState(AttackState::INACTIVE);
}

void Player::Draw(SpriteExtensions &spriteBatch)
{
	GameObject::Draw(spriteBatch);
	
	whip->Draw(spriteBatch);
	
	for (auto &weapon : secondaryWeapons)
		weapon->Draw(spriteBatch);
}

void Player::DrawBoundingBox(SpriteExtensions &spriteBatch)
{
	GameObject::DrawBoundingBox(spriteBatch);
	whip->DrawBoundingBox(spriteBatch);
}

#pragma region Commands

void Player::Idle()
{
	SetMoveState(MoveState::IDLE);
	velocity.x = 0.0f;
}

void Player::WalkLeft()
{
	SetMoveState(MoveState::WALKING);
	SetFacing(Facing::Left);
	velocity.x = -speed;
}

void Player::WalkRight()
{
	SetMoveState(MoveState::WALKING);
	SetFacing(Facing::Right);
	velocity.x = speed;
}

void Player::Jump()
{
	SetMoveState(MoveState::JUMPING);
	velocity.y = -jumpSpeed;
}

void Player::Duck()
{
	SetMoveState(MoveState::DUCKING);
	velocity = Vector2::Zero();
}

void Player::Attack()
{
	SetAttackState(AttackState::WHIPPING);
	whip->Unleash();
}

void Player::Throw(std::unique_ptr<RangedWeapon> weapon)
{
	if (data.hearts == 0)
		return;

	weapon->SetOwner(this);
	weapon->GetBody().Enabled(false);
	weapon->SetVisibility(false);

	SetAttackState(AttackState::THROWING);
	secondaryWeapons.push_back(std::move(weapon));

	data.hearts--;

	if (data.hearts == 0)
	{
		data.secondaryWeapon = EntityType::Unknown;
	}
}

void Player::TurnBackward()
{
	SetMoveState(MoveState::TURNING_BACKWARD);
	velocity = Vector2::Zero();
}

void Player::DoThrow()
{
	// Launch the most recently added weapon
	auto &weapon = secondaryWeapons.back();

	if (weapon->GetState() == RangedWeaponState::Sheathed)
		weapon->Throw();
}

void Player::Land()
{
	if (velocity.y > 600.0f) // Falling down very fast, do a superhero landing
	{
		SetMoveState(MoveState::LANDING_HARD);
		velocity = Vector2::Zero();
		landingTimer.Start();
	}
	else
	{
		if (attackState == AttackState::WHIPPING
			|| attackState == AttackState::THROWING)
		{
			velocity.x = 0; // Still keep attacking on the ground but not moving anymore
			moveState = MoveState::IDLE; // Set moveState so the character know what to do when finish attacking
		}
		else
			Idle();
	}
}

void Player::Flash()
{
	SetMoveState(MoveState::FLASHING);
	velocity = Vector2::Zero();
}

#pragma endregion