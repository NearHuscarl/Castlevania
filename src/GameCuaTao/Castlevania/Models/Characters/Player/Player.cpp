#include "Direct2DGame/Input/InputHelper.h"
#include "Player.h"
#include "../../Settings.h"
#include "../../UpdateData.h"

using namespace Castlevania;

// in milliseconds
constexpr auto LANDING_TIME = 400;
constexpr auto FLASHING_TIME = 900;
constexpr auto UNTOUCHABLE_TIME = 2000;

// Simon bounce back's max height (when taking damage)
constexpr auto BOUNCE_BACK_HEIGHT = 360.0f;

Player::Player() : GameObject{ EntityType::Player }
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

MoveState Player::GetMoveState()
{
	return moveState;
}

AttackState Player::GetAttackState()
{
	return attackState;
}

void Player::SetSpeed(float speed)
{
	GameObject::SetSpeed(speed);
	stairWalkingSpeed = speed / 2;
}

void Player::SetJumpSpeed(float jumpSpeed)
{
	this->jumpSpeed = jumpSpeed;
}

void Player::AddExp(int amount)
{
	data.score += amount;
}

void Player::SetWhip(std::unique_ptr<Whip> whip)
{
	this->whip = std::move(whip);
}

EntityType Player::GetSubWeapon()
{
	return data.subWeapon;
}

void Player::SetSubWeapon(EntityType weapon)
{
	//subWeapon->GetBody().Enabled(false);
	data.subWeapon = weapon;
}

void Player::LoadContent(ContentManager &content)
{
	GameObject::LoadContent(content);
	Idle();
}

void Player::Update(GameTime gameTime, UpdateData &updateData)
{
	if (InputHelper::IsKeyDown(DIK_9)) // NOTE: remove debugging code
		data.hearts += 20;
	else if (InputHelper::IsKeyDown(DIK_0))
		data.health = MAX_HEALTH;

	GameObject::Update(gameTime, updateData);
	UpdateStates();
	UpdateSubWeapons(updateData);

	whip->Update(gameTime, updateData);
}

void Player::UpdateStates()
{
	switch (moveState)
	{
		case MoveState::WALKING_TO_STAIRS:
		{
			auto playerCenter_x = GetOriginPosition().x;
			auto stairCenter_x = nearbyStair->GetOriginPosition().x;

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
			if (landingTimer.ElapsedMilliseconds() >= LANDING_TIME)
			{
				landingTimer.Reset();
				Idle();
			}
			break;

		case MoveState::FLASHING:
			if (flashingTimer.ElapsedMilliseconds() >= FLASHING_TIME)
			{
				flashingTimer.Reset();
				Idle();
			}
			break;
	}

	if (untouchableTimer.ElapsedMilliseconds() > UNTOUCHABLE_TIME)
	{
		untouchableTimer.Reset();
		SendMessageToSystems(UNTOUCHABLE_ENDED);
	}
}

void Player::UpdateSubWeapons(UpdateData &updateData)
{
	auto objectCollection = updateData.objectCollection;

	if (subWeapon == nullptr || objectCollection == nullptr)
		return;

	if (subWeapon->GetBody().Enabled()) // weapon is flying and active
		objectCollection->entities.push_back(std::move(subWeapon));
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
	auto stairCenter_x = nearbyStair->GetOriginPosition().x;
	
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
		velocity.x = -stairWalkingSpeed;
	else
		velocity.x = stairWalkingSpeed;
	velocity.y = -stairWalkingSpeed;
}

void Player::GoDownstairs()
{
	if (moveState == MoveState::IDLE_UPSTAIRS)
		SwitchFacing();
	
	SetMoveState(MoveState::GOING_DOWNSTAIRS);

	if (facing == Facing::Left)
		velocity.x = -stairWalkingSpeed;
	else
		velocity.x = stairWalkingSpeed;
	velocity.y = stairWalkingSpeed;
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

	subWeapon = std::move(weapon);
	subWeapon->SetOwner(this);
	subWeapon->GetBody().Enabled(false);
	subWeapon->SetVisibility(false);

	SetAttackState(AttackState::THROWING);

	data.hearts--;

	if (data.hearts == 0)
	{
		data.subWeapon = EntityType::Unknown;
	}
}

void Player::TurnBackward()
{
	SetMoveState(MoveState::TURNING_BACKWARD);
	velocity = Vector2::Zero();
}

bool Player::IsAttacking()
{
	return attackState == AttackState::WHIPPING || attackState == AttackState::THROWING;
}

bool Player::IsOnStairs()
{
	return moveState == MoveState::GOING_UPSTAIRS
		|| moveState == MoveState::GOING_DOWNSTAIRS
		|| moveState == MoveState::IDLE_UPSTAIRS
		|| moveState == MoveState::IDLE_DOWNSTAIRS;
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
	velocity.x = 0;
}

void Player::DoThrow()
{
	if (subWeapon == nullptr)
		return;

	subWeapon->Throw();
}

void Player::Land()
{
	if (IsAttacking())
	{
		velocity.x = 0; // Still keep attacking on the ground but not moving anymore
		moveState = MoveState::IDLE; // Set moveState so the character know what to do when finish attacking
		return;
	}

	if (velocity.y > 600.0f) // Falling down very fast, do a superhero landing
	{
		SetMoveState(MoveState::LANDING_HARD);
		velocity = Vector2::Zero();
		landingTimer.Start();
	}
	else
	{
		Idle();
	}
}

void Player::Flash()
{
	SetMoveState(MoveState::FLASHING);
	velocity = Vector2::Zero();
	flashingTimer.Start();
}

void Player::TakeDamage(int damage, Direction direction)
{
	if (untouchableTimer.IsRunning())
		return;

	if (direction == Direction::Left)
	{
		SetFacing(Facing::Left);
		velocity.x = speed;
	}
	else if (direction == Direction::Right)
	{
		SetFacing(Facing::Right);
		velocity.x = -speed;
	}

	velocity.y = -BOUNCE_BACK_HEIGHT;

	SetMoveState(MoveState::TAKING_DAMAGE);
	data.health -= damage;
	whip->Withdraw();
	untouchableTimer.Start();
}

#pragma endregion