#include "Direct2DGame/MathHelper.h"
#include "Direct2DGame/Input/Keyboard.h"
#include "Direct2DGame/Input/InputHelper.h"
#include "Player.h"
#include "../../Settings.h"
#include "../../UpdateData.h"
#include "../../../Scenes/Stages/StageEvent.h"
#include "../../../Utilities/AudioManager.h"
#include "../../../Utilities/CollisionGrid.h"

using namespace Castlevania;

// in milliseconds
constexpr auto LANDING_TIME = 400;
constexpr auto FLASHING_TIME = 900;
constexpr auto UNTOUCHABLE_TIME = 2000;
constexpr auto THROWING_COOLDOWN_TIME = 1000;
constexpr auto INVISIBLE_TIME = 6000;
constexpr auto LARGE_HEIGHT = 32 * 2.5f; // 2.5 tiles

// Simon bounce back's max height (when taking damage)
constexpr auto BOUNCE_BACK_HEIGHT = 360.0f;

// velocity to trigger hovering state
constexpr auto HOVERING_VELOCITY = 20.0f;

Player::Player() : GameObject{ ObjectId::Player }
{
	subWeaponCount = 1;
}

Player::~Player()
{
	Keyboard::Register(nullptr);
}

void Player::SetMoveState(MoveState moveState)
{
	this->moveState = moveState;
	SendMessageToSystems(MOVE_STATE_CHANGED);
}

void Player::SetAttackState(AttackState attackState)
{
	if (moveState == MoveState::WALKING)
		Idle();

	this->attackState = attackState;
	SendMessageToSystems(ATTACK_STATE_CHANGED);
}

const PlayerData &Player::GetData()
{
	return data;
}

const NearbyObjects Player::GetNearbyObjects()
{
	return nearbyObjects;
}

MoveState Player::GetMoveState()
{
	return moveState;
}

AttackState Player::GetAttackState()
{
	return attackState;
}

void Player::SetPosition(Checkpoint checkpoint)
{
	position = checkpoint.position;
	SetFacing(checkpoint.facing);
	lastPlatformHeight = position.y + GetFrameRect().Height();
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

void Player::SetFacing(Facing facing)
{
	GameObject::SetFacing(facing);
	whip->SetFacing(facing);
}

void Player::AddExp(int amount)
{
	data.score += amount;
}

void Player::AddHeart(int amount)
{
	data.hearts += amount;
}

void Player::SetWhip(std::unique_ptr<Whip> whip)
{
	this->whip = std::move(whip);
	this->whip->SetOwner(this);
}

ObjectId Player::GetSubWeapon()
{
	return data.subWeapon;
}

void Player::SetSubWeapon(ObjectId weapon)
{
	//subWeapon->GetBody().Enabled(false);
	data.subWeapon = weapon;
}

void Player::LoadContent(ContentManager &content)
{
	GameObject::LoadContent(content);
	Idle();
}

void Player::Update(UpdateData &updateData)
{
	GameObject::Update(updateData);
	UpdateStates();
	data.health.Update();
	isStopwatchActive = updateData.isStopwatchActive;

	whip->Update(updateData);
}

void Player::UpdateStates()
{
	switch (moveState)
	{
		case MoveState::WALKING_TO_STAIRS:
		{
			if (nearbyObjects.stair == nullptr) // This should not happen. But life finds a way so here is a temporary fix
				Idle();

			auto stairCenter_x = nearbyObjects.stair->GetOriginPosition().x;
			auto stairBbox = nearbyObjects.stair->GetBoundingBox();

			if (facing == Facing::Left)
			{
				if (GetBoundingBox().left <= stairBbox.left)
					OnHitStairEntry();
			}
			else
			{
				if (GetBoundingBox().right >= stairBbox.right)
					OnHitStairEntry();
			}
			break;
		}
		case MoveState::JUMPING:
			if (velocity.y >= -HOVERING_VELOCITY)
				SetMoveState(MoveState::HOVERING);
			break;

		case MoveState::HOVERING:
			if (velocity.y >= HOVERING_VELOCITY)
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

	if (invisibleTimer.ElapsedMilliseconds() > INVISIBLE_TIME)
	{
		AudioManager::Play(SE_INVISIBLE_END);
		invisibleTimer.Reset();
		SendMessageToSystems(INVISIBLE_ENDED);
	}
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
		case MoveState::IDLE_UPSTAIRS:
		case MoveState::IDLE_DOWNSTAIRS:
			Idle();
			break;

		case MoveState::JUMPING:
		case MoveState::HOVERING:
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
	auto nearbyStair = nearbyObjects.stair;
	auto triggerType = nearbyStair->GetTriggerType();
	auto stairFacing = nearbyStair->GetFacing();

	SetFacing(stairFacing);

	if (triggerType == TriggerType::STAIR_UP)
		GoUpstairs();
	else if (triggerType == TriggerType::STAIR_DOWN)
		GoDownstairs();
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
		case MoveState::IDLE_UPSTAIRS:
			SetMoveState(MoveState::IDLE_UPSTAIRS);
			velocity = Vector2::Zero();
			break;

		case MoveState::GOING_DOWNSTAIRS:
		case MoveState::IDLE_DOWNSTAIRS:
			SetMoveState(MoveState::IDLE_DOWNSTAIRS);
			velocity = Vector2::Zero();
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
	auto nearbyStair = nearbyObjects.stair;

	if (nearbyStair == nullptr)
		return;

	auto playerCenter_x = GetOriginPosition().x;
	auto stairCenter_x = nearbyStair->GetOriginPosition().x;
	
	if (playerCenter_x < stairCenter_x)
	{
		SetFacing(Facing::Right);
		velocity.x = speed;
	}
	else // (playerCenter_x >= stairCenter_x)
	{
		SetFacing(Facing::Left);
		velocity.x = -speed;
	}

	SetMoveState(MoveState::WALKING_TO_STAIRS);
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
	if (moveState == MoveState::GOING_UPSTAIRS
		|| moveState == MoveState::GOING_DOWNSTAIRS)
	{
		return;
	}

	SetAttackState(AttackState::WHIPPING);
	whip->Unleash();
}

void Player::Stoptime()
{
	if (isStopwatchActive || data.hearts < 5)
		return;

	data.hearts = MathHelper::Max(data.hearts - 5, 0);
	Notify(STOPWATCH_POWERUP_ACTIVATED);

	if (data.hearts == 0)
		data.subWeapon = ObjectId::Unknown;
}

void Player::Throw(std::unique_ptr<RangedWeapon> weapon)
{
	if (subWeaponCount == 0)
	{
		if (throwingCooldownTimer.ElapsedMilliseconds() < THROWING_COOLDOWN_TIME)
			return;
		else
		{
			if (data.powerup == ObjectId::DoubleShot)
				subWeaponCount = 2;
			else
				subWeaponCount = 1;

			throwingCooldownTimer.Reset();
		}
	}

	if (subWeaponCount == 1)
		throwingCooldownTimer.Start();

	subWeaponCount = MathHelper::Max(--subWeaponCount, 0);

	if (data.hearts == 0)
		return;

	subWeapon = std::move(weapon);
	subWeapon->GetBody().Enabled(false);
	subWeapon->SetVisibility(false);

	SetAttackState(AttackState::THROWING);

	data.hearts--;

	if (data.hearts == 0)
		data.subWeapon = ObjectId::Unknown;
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

bool Player::IsOnTheAir()
{
	return moveState == MoveState::JUMPING
		|| moveState == MoveState::HOVERING
		|| moveState == MoveState::FALLING
		|| moveState == MoveState::FALLING_HARD
		|| moveState == MoveState::LANDING
		|| moveState == MoveState::TAKING_DAMAGE;
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
	auto nearbyStair = nearbyObjects.stair;

	if (nearbyStair == nullptr)
		return false;
	
	return nearbyStair->GetTriggerType() == TriggerType::STAIR_UP;
}

bool Player::CanGoDownstairs()
{
	auto nearbyStair = nearbyObjects.stair;

	if (nearbyStair == nullptr)
		return false;

	return nearbyStair->GetTriggerType() == TriggerType::STAIR_DOWN;
}

void Player::IdleOnGround()
{
	lastPlatformHeight = position.y + GetFrameRect().Height();
	SetMoveState(MoveState::IDLE);
	velocity.x = 0;
}

void Player::DoThrow()
{
	if (subWeapon == nullptr)
		return;

	auto playerBbox = GetBoundingBox();
	auto position = Vector2{
		playerBbox.left,
		playerBbox.top + 5
	};

	subWeapon->SetFacing(facing);
	subWeapon->Throw(position);
	collisionGrid->Add(std::move(subWeapon), CollisionObjectType::Entity);
}

void Player::Fall()
{
	velocity.x = 0.0f;
	moveState = MoveState::FALLING_HARD;
}

void Player::Land()
{
	if (state != ObjectState::NORMAL)
		return;

	if (IsAttacking())
	{
		velocity.x = 0; // Still keep attacking on the ground but not moving anymore
		moveState = MoveState::IDLE; // Set moveState so the character know what to do when finish attacking
		return;
	}

	// Falling down at great distance, do a superhero landing
	if (position.y + GetFrameRect().Height() - lastPlatformHeight >= LARGE_HEIGHT)
	{
		SetMoveState(MoveState::LANDING_HARD);
		velocity = Vector2::Zero();
		AudioManager::Play(SE_LANDING);
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
	whip->Withdraw();
	flashingTimer.Start();
}

void Player::BecomeInvisible()
{
	AudioManager::Play(SE_INVISIBLE_START);
	invisibleTimer.Start();
	SendMessageToSystems(INVISIBLE_STARTED);
}

void Player::TakeDamage(int damage, Direction direction)
{
	if (untouchableTimer.IsRunning() || invisibleTimer.IsRunning() || godMode)
		return;

	if (IsOnStairs() && data.health.Value() - damage <= 0)
		Fall(); // fall to dealth literally ~.~
	else if (!IsOnStairs())
		BounceBack(direction);

	data.health.Add(-damage);
	untouchableTimer.Start();
	AudioManager::Play(SE_BEING_HIT);
	SendMessageToSystems(UNTOUCHABLE_STARTED);
}

void Player::BounceBack(Direction direction)
{
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
	whip->Withdraw();
}

void Player::ToggleGodMode()
{
	godMode = !godMode;

	if (godMode)
		SendMessageToSystems(GOD_MODE_ACTIVATED);
	else
		SendMessageToSystems(GOD_MODE_DEACTIVATED);
}

void Player::Die()
{
	if (state != ObjectState::NORMAL || godMode)
		return;

	velocity.x = 0.0f;
	controlSystem->Enabled(false);
	AudioManager::Play(SE_LIVE_LOST);
	SetState(ObjectState::DYING);
}

void Player::Revive()
{
	data.health = Health{ MAX_HEALTH };
	data.hearts = DEFAULT_HEART_COUNT;
	data.subWeapon = ObjectId::Unknown;
	data.lives--;

	Idle();
	EnableControl(true);
	SetState(ObjectState::NORMAL);
}

#pragma endregion