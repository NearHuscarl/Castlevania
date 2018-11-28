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

void Player::Update(GameTime gameTime, UpdateData &updateData)
{
	if (InputHelper::IsKeyDown(DIK_9)) // NOTE: remove debugging code
		data.hearts += 20;
	else if (InputHelper::IsKeyDown(DIK_0))
		data.playerHealth = MAX_HEALTH;

	GameObject::Update(gameTime, updateData);
	UpdateStates();

	whip->Update(gameTime, updateData);

	for (auto &weapon : secondaryWeapons)
		weapon->Update(gameTime, updateData);
}

void Player::UpdateStates()
{
	switch (moveState)
	{
		case MoveState::WALKING_TO_STAIRS:
		{
			auto playerCenter_x = GetOriginPosition().x;
			auto stairCenter_x = nearbyStair->Center().x;

			if (playerCenter_x >= stairCenter_x && facing == Facing::Right
				|| playerCenter_x <= stairCenter_x && facing == Facing::Left)
				OnHitStairEntry();
			break;
		}
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

void Player::OnHitStairEntry()
{
	auto triggerType = nearbyStair->GetTriggerType();
	auto stairFacing = nearbyStair->GetFacing();

	SetFacing(stairFacing);

	if (triggerType == TriggerType::STAIR_UP)
		GoUpstairs();
	else if (triggerType == TriggerType::STAIR_DOWN)
		GoDownstairs();
}

void Player::OnStopClimbingStair()
{
	velocity = Vector2::Zero();
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
	switch (moveState)
	{
		case MoveState::GOING_UPSTAIRS:
			SetMoveState(MoveState::IDLE_UPSTAIRS);
			break;

		case MoveState::GOING_DOWNSTAIRS:
			SetMoveState(MoveState::IDLE_DOWNSTAIRS);
			break;

		default:
			IdleOnGround();
			break;
	}
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

void Player::WalkToStairs()
{
	if (nearbyStair == nullptr)
		return;

	auto playerCenter_x = GetOriginPosition().x;
	auto stairCenter_x = nearbyStair->Center().x;
	
	if (playerCenter_x < stairCenter_x)
	{
		SetFacing(Facing::Right);
		velocity.x = speed;
		SetMoveState(MoveState::WALKING_TO_STAIRS);
	}
	else // (playerCenter_x >= stairCenter_x)
	{
		SetFacing(Facing::Left);
		velocity.x = -speed;
		SetMoveState(MoveState::WALKING_TO_STAIRS);
	}
}

void Player::GoUpstairs()
{
	if (moveState == MoveState::IDLE_DOWNSTAIRS) // TODO: add MOVING_DOWNSTAIR?
		SwitchFacing();
	
	SetMoveState(MoveState::GOING_UPSTAIRS);

	if (facing == Facing::Left)
		velocity.x = -speed / 2;
	else
		velocity.x = speed / 2;
	velocity.y = -speed / 2;
}

void Player::GoDownstairs()
{
	if (moveState == MoveState::IDLE_UPSTAIRS)
		SwitchFacing();
	
	SetMoveState(MoveState::GOING_DOWNSTAIRS);

	if (facing == Facing::Left)
		velocity.x = -speed / 2;
	else
		velocity.x = speed / 2;
	velocity.y = speed / 2;
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

bool Player::CanGoUpstairs()
{
	if (nearbyStair == nullptr)
		return false;
	
	return nearbyStair->GetTriggerType() == TriggerType::STAIR_UP;
}

bool Player::CanGoDownstairs()
{
	if (nearbyStair == nullptr)
		return false;

	return nearbyStair->GetTriggerType() == TriggerType::STAIR_DOWN;
}

void Player::IdleOnGround()
{
	SetMoveState(MoveState::IDLE);
	velocity.x = 0.0f;
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